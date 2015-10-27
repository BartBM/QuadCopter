#include "mpu9250.h"
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include <bitset>
#include <chrono>
#include "../events/imuevent.h"

using namespace std;

MPU9250::MPU9250() : I2CChip()
{
    cout << endl << "==> MPU 9250" << endl;
    accelEnabled = false;
    gyroEnabled = false;
    magEnabled = false;
}

MPU9250::~MPU9250()
{

}

void MPU9250::init(I2CDataBus *i2cDataBus)
{
    I2CChip::init(i2cDataBus);
    ak8963.init(i2cDataBus);
}

void MPU9250::reset()
{
    write({PWR_MGMT_01,     0x80}); //reset
    usleep(100000);
}

void MPU9250::configure()
{
    reset();
    write({PWR_MGMT_01,     0x00}); //disable sleep mode
    usleep(200000);

    write({PWR_MGMT_01,     0x01}); //select accel x as time source

    write({CONFIG,          0x03});
    write({PWR_MGMT_02,     0x00});

    setSamplerateDivider(5);
    setGyroConfigScale(GyroScale::_1000dps);
    setAccelConfigScale(AccelScale::_8g);
    write({ACCEL_CONFIG2,   0b00001011});
    usleep(100000);

    write({INT_PIN_CFG,     0x22});
    write({INT_ENABLE,      0x00});
    write({FIFO_EN,         0x00});
    usleep(100000);
}

void MPU9250::configureCompass()
{
    write({PWR_MGMT_01, 0x01}); //disable sleep

    setI2CBypass(true);
    usleep(100000);

    ak8963.configure();
}

void MPU9250::enableFifo(bool gyro, bool accel, bool compass)
{
    cout << "[MPU9250 enableFifo]" << endl;

    gyroEnabled = gyro;
    accelEnabled = accel;
    magEnabled = compass;

    if (gyro || accel || compass) {
        write({USER_CTRL, 0x40}); // enable FIFO
    }
    usleep(100000);

    unsigned char enabledSensors = 0;

    if (gyroEnabled) {
        enabledSensors |= 0b01110000;
    }

    if (accelEnabled) {
        enabledSensors |= 0b00001000;
    }

    if (magEnabled) {
        enabledSensors |= 0b00000011;

        write({I2C_SLV0_ADDR, static_cast<unsigned char>(0x80 | ak8963.getSlaveAddr())});
        write({I2C_SLV0_REG, ak8963.getStartReadAddr()});
        write({I2C_SLV0_CTRL, 0x88});

        write({I2C_SLV1_ADDR, ak8963.getSlaveAddr()});
        write({I2C_SLV1_REG, 0x0A});
        write({I2C_SLV1_CTRL, 0x81});
        write({I2C_SLV1_DO, 0x01 | ak8963.getOutputBitSetting()});

        write({I2C_SLV4_CTRL, 0x04});
        write({I2C_MST_DELAY_CTRL, 0x03});        


    }

    write({FIFO_EN, enabledSensors});
}

void MPU9250::pauseFifo()
{
    write({FIFO_EN, 0x00});
}

void MPU9250::calibrateSensors()
{
    cout << "[MPU9250 calibrateSensors]" << endl;
    readBiases();
    calibrateGyro();
    calibrateAccel();
    //readBiases(); // TODO remove
}

void MPU9250::readBiases()
{
    cout << "[MPU9250 readBiases]" << endl;
    write({PWR_MGMT_01,     0x80});
    usleep(100000);

    //write({PWR_MGMT_01,     0x01});
    write({PWR_MGMT_02,     0x00});
    usleep(100000);

    //write({INT_ENABLE,      0x00});
    //write({FIFO_EN,         0x00});
    //write({PWR_MGMT_01,     0x00});
    //write({I2C_MST_CTRL,    0x00});
    //write({USER_CTRL,       0x00});
    //write({USER_CTRL,       0x0C}); // DMP_RST & FIFO_RST
    usleep(15000);

    write({CONFIG,          0x03});

    setSamplerateDivider(10);
    setGyroConfigScale(GyroScale::_1000dps);
    setAccelConfigScale(AccelScale::_8g);
    usleep(200000);

    int total_packets = 0;

    while (total_packets < 150) {
        enableFifo(true, true, false);
        usleep(200000);
        pauseFifo();

        int packet_counter = getFifoCount() / 12;
        cout << "\tNr of packets: " << dec << packet_counter << endl;

        for (int i=0; i<packet_counter; i++) {

            vector<unsigned char> data = readValues<unsigned char>(FIFO_R_W, 12);

            vec3_accel_bias.setX(vec3_accel_bias.getX() + (short) (((short) data[0] << 8) | data[1]));
            vec3_accel_bias.setY(vec3_accel_bias.getY() + (short) (((short) data[2] << 8) | data[3]));
            vec3_accel_bias.setZ(vec3_accel_bias.getZ() + (short) (((short) data[4] << 8) | data[5]));
            //cout << (vec3_accel_bias / (total_packets + i +1)).toString() << endl;

            vec3_gyr_bias.setX(vec3_gyr_bias.getX() + (short) (((short) data[6]  << 8) | data[7]));
            vec3_gyr_bias.setY(vec3_gyr_bias.getY() + (short) (((short) data[8]  << 8) | data[9]));
            vec3_gyr_bias.setZ(vec3_gyr_bias.getZ() + (short) (((short) data[10] << 8) | data[11]));
        }

        total_packets += packet_counter;
    }

    vec3_accel_bias /= total_packets;
    vec3_gyr_bias /= total_packets;

    if (vec3_accel_bias.getZ() > 0L)
        vec3_accel_bias.setZ(vec3_accel_bias.getZ() - getAccelSensitivity());
    else
        vec3_accel_bias.setZ(vec3_accel_bias.getZ() + getAccelSensitivity());

    vec3_accel_bias /= 2;

    cout << "\tAccel bias: " << vec3_accel_bias.toString() << endl;
    cout << "\tGyro bias: " << vec3_gyr_bias.toString() << endl;

}

void MPU9250::calibrateGyro()
{
    cout << "[MPU9250 calibrateGyro]" << endl;

    vec3_gyr_bias *= -1;

    cout << vec3_gyr_bias.toString() << endl;

    write({XG_OFFSET_H, static_cast<unsigned char>((vec3_gyr_bias.getX() >> 8) & 0xFF) });
    write({XG_OFFSET_L, static_cast<unsigned char>(vec3_gyr_bias.getX()  & 0xFF) });

    write({YG_OFFSET_H, static_cast<unsigned char>((vec3_gyr_bias.getY() >> 8) & 0xFF) });
    write({YG_OFFSET_L, static_cast<unsigned char>(vec3_gyr_bias.getY() & 0xFF) });

    write({ZG_OFFSET_H, static_cast<unsigned char>((vec3_gyr_bias.getZ() >> 8) & 0xFF) });
    write({ZG_OFFSET_L, static_cast<unsigned char>(vec3_gyr_bias.getZ() & 0xFF) });
}

void MPU9250::calibrateAccel()
{
    cout << "[MPU9250 calibrateAccel]" << endl;

    Vector3<long> vec3_accel_reg_bias;
    vec3_accel_reg_bias.setX(((long) readValue<unsigned char>(XA_OFFSET_H) << 8) | readValue<unsigned char>(XA_OFFSET_L));
    vec3_accel_reg_bias.setY(((long) readValue<unsigned char>(YA_OFFSET_H) << 8) | readValue<unsigned char>(YA_OFFSET_L));
    vec3_accel_reg_bias.setZ(((long) readValue<unsigned char>(ZA_OFFSET_H) << 8) | readValue<unsigned char>(ZA_OFFSET_L));

    cout << vec3_accel_reg_bias.toString() << endl;
    vec3_accel_reg_bias -= ((vec3_accel_bias) & ~1);
    cout << vec3_accel_reg_bias.toString() << endl;

    write({XA_OFFSET_H, static_cast<unsigned char>((vec3_accel_reg_bias.getX() >> 8) & 0xFF) });
    write({XA_OFFSET_L, static_cast<unsigned char>(vec3_accel_reg_bias.getX() & 0xFF) });

    write({YA_OFFSET_H, static_cast<unsigned char>((vec3_accel_reg_bias.getY() >> 8) & 0xFF) });
    write({YA_OFFSET_L, static_cast<unsigned char>(vec3_accel_reg_bias.getY() & 0xFF) });

    write({ZA_OFFSET_H, static_cast<unsigned char>((vec3_accel_reg_bias.getZ() >> 8) & 0xFF) });
    write({ZA_OFFSET_L, static_cast<unsigned char>(vec3_accel_reg_bias.getZ() & 0xFF) });
}

void MPU9250::selfTest()
{
    gyroSelfTest.setX((int) readValue<unsigned char>(SELF_TEST_X_GYRO));
    gyroSelfTest.setY((int) readValue<unsigned char>(SELF_TEST_Y_GYRO));
    gyroSelfTest.setZ((int) readValue<unsigned char>(SELF_TEST_Z_GYRO));

    accelSelfTest.setX((int) readValue<unsigned char>(SELF_TEST_X_ACCEL));
    accelSelfTest.setY((int) readValue<unsigned char>(SELF_TEST_Y_ACCEL));
    accelSelfTest.setZ((int) readValue<unsigned char>(SELF_TEST_Z_ACCEL));

    Vector3<long> gyroReadWoST;
    Vector3<long> accelReadWoST;

    for (int i=0; i<SELF_TEST_SAMPLES; i++) {
        gyroReadWoST += readGyro();
        accelReadWoST += readAccel();
    }

    gyroReadWoST /= SELF_TEST_SAMPLES;
    accelReadWoST /= SELF_TEST_SAMPLES;

    cout << gyroReadWoST.toString() << endl;

    Vector3<long> gyroReadWST;
    Vector3<long> accelReadWST;

    setGyroSelfTest(true);
    setAccelSelfTest(true);

    for (int i=0; i<SELF_TEST_SAMPLES; i++) {
        gyroReadWST += readGyro();
        accelReadWST += readAccel();
    }

    setGyroSelfTest(false);
    setAccelSelfTest(false);

    gyroReadWST /= SELF_TEST_SAMPLES;
    accelReadWST /= SELF_TEST_SAMPLES;

    cout << gyroReadWST.toString() << endl;


    Vector3<long> gyroResult = gyroReadWST - gyroReadWoST;
    Vector3<long> accelResult = accelReadWST - accelReadWoST;

    cout << "\tSelftest gyro (result): " << gyroResult.toString() << endl;
    cout << "\tSelftest gyro (factory): " << gyroSelfTest.toString() << endl;

    cout << "\tSelftest (result): " << accelResult.toString() << endl;
    cout << "\tSelftest accel (factory): " << accelSelfTest.toString() << endl;
}

short MPU9250::getFifoCount()
{
    return ((short) readValue<unsigned char>(FIFO_COUNTH)) << 8 | readValue<unsigned char>(FIFO_COUNTL);
}

void MPU9250::readFifoStream()
{
    cout << "[MPU9250 readFifoStream]" << endl;

    write({I2C_MST_CTRL,    0x0D}); // set I2C master clock to 400 kHz

    int packetCount;
    Vector3<short> gyro, accel, mag;
    int package_size = 0 + ((gyroEnabled)? 6 : 0) + ((accelEnabled)? 6 : 0) + ((magEnabled)? 8 : 0);

    chrono::time_point<chrono::system_clock> timeStart = chrono::system_clock::now();

    for (int i=0; i<10000; i++) {
        packetCount = getFifoCount() / package_size;

        while (packetCount < 2) {
            usleep(500);
            packetCount = getFifoCount() / package_size;
            cout << "wait - not enough packets: " << packetCount << endl;
        }

        vector<unsigned char> data = readValues<unsigned char>(FIFO_R_W, package_size);
        int s = 0;
        if (accelEnabled) {
            accel.setX((short) (((short) data[0] << 8) | data[1]));
            accel.setY((short) (((short) data[2] << 8) | data[3]));
            accel.setZ((short) (((short) data[4] << 8) | data[5]));
            s+=6;
        }

        if (gyroEnabled) {
            gyro.setX((short) (((short) data[s + 0] << 8) | data[s + 1]));
            gyro.setY((short) (((short) data[s + 2] << 8) | data[s + 3]));
            gyro.setZ((short) (((short) data[s + 4] << 8) | data[s + 5]));
            s+=6;
        }

        if (magEnabled) {
            s+=1;
            mag.setX((short) (((short) data[s + 1] << 8) | data[s + 0]));
            mag.setY((short) (((short) data[s + 3] << 8) | data[s + 2]));
            mag.setZ((short) (((short) data[s + 5] << 8) | data[s + 4]));
        }

        //cout << "packet count" << packetCount << "\t" << gyro.toString() << "\t" << accel.toString() << "\t" << bitset<8>(data[12]) << " " << bitset<8>(data[19]) << " " << mag.toString() << endl;

        convertAndDispatch(gyro, accel, mag);

    }

    cout << "Duration: " << dec << chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - timeStart).count() << endl;

}

void MPU9250::convertAndDispatch(Vector3<short>& gyro, Vector3<short>& accel, Vector3<short>& mag)
{
    ImuEvent imuEvent;
    imuEvent.setData(((Vector3<float>) gyro) / getGyroSensitivity(), ((Vector3<float>) accel) / getAccelSensitivity(), mag);

    notify(&imuEvent);
}

void MPU9250::setSamplerateDivider(int sampleRateDivider)
{
    this->sampleRateDivider = sampleRateDivider - 1;
    write({SMPLRT_DIV, static_cast<unsigned char>(this->sampleRateDivider & 0xFF)});

}

Vector3<short> MPU9250::readGyro()
{
    short x =  (((short) readValue<unsigned char>(GYRO_XOUT_H)) << 8) & 0xFF00;
    x |= ((short) readValue<unsigned char>(GYRO_XOUT_L));

    short y =  (((short) readValue<unsigned char>(GYRO_YOUT_H)) << 8) & 0xFF00;
    y |= ((short) readValue<unsigned char>(GYRO_YOUT_L));

    short z =  (((short) readValue<unsigned char>(GYRO_ZOUT_H)) << 8) & 0xFF00;
    z |= ((short) readValue<unsigned char>(GYRO_ZOUT_L));

    return Vector3<short>(x, y, z);
}

Vector3<short> MPU9250::readAccel()
{    
    short x =  ((short) readValue<unsigned char>(ACCEL_XOUT_H)) << 8;
    x |= ((short) readValue<unsigned char>(ACCEL_XOUT_L));

    short y =  ((short) readValue<unsigned char>(ACCEL_YOUT_H)) << 8;
    y |= ((short) readValue<unsigned char>(ACCEL_YOUT_L));

    short z =  ((short) readValue<unsigned char>(ACCEL_ZOUT_H)) << 8;
    z |= ((short) readValue<unsigned char>(ACCEL_ZOUT_L));

    return Vector3<short>(x, y, z);
}

Vector3<short> MPU9250::readCompass()
{
    vector<unsigned char> magData = readValues<unsigned char>(EXT_SENS_DATA_00, 8);

    Vector3<short> mag;
    mag.setX((short) (((short) magData[2] << 8) | magData[1]));
    mag.setY((short) (((short) magData[4] << 8) | magData[3]));
    mag.setZ((short) (((short) magData[6] << 8) | magData[5]));

    return mag;
}

void MPU9250::whoAmi()
{
    cout << "[MPU9250 whoAmI]" << endl;

    unsigned char whoAmI = readValue<unsigned char>(0x75);

    cout << "\tI am: " << hex << (int) whoAmI << endl;
    if (whoAmI != 0x71){
        throw runtime_error("WhoAmI value");
    }
}

void MPU9250::setGyroSelfTest(bool enabled)
{
    unsigned char gyro_conf = readValue<unsigned char>(GYRO_CONFIG);
    if (enabled) {
        gyro_conf |=  ((1 << 7) | (1 << 6) | (1 << 5));
    } else {
        gyro_conf &= ~((1 << 7) | (1 << 6) | (1 << 5));
    }
    write({GYRO_CONFIG, gyro_conf});
}

void MPU9250::setAccelSelfTest(bool enabled)
{
    unsigned char accel_conf = readValue<unsigned char>(ACCEL_CONFIG);
    if (enabled) {
        accel_conf |=  ((1 << 7) | (1 << 6) | (1 << 5));
    } else {
        accel_conf &= ~((1 << 7) | (1 << 6) | (1 << 5));
    }
    write({ACCEL_CONFIG, accel_conf});
}

void MPU9250::setI2CBypass(bool enabled)
{
    unsigned char user_control = readValue<unsigned char>(USER_CTRL);
    //cout << "user_control: " << bitset<8>(user_control) << endl;
    if (!enabled) {
         user_control |= 1 << 5;
    } else {
         user_control &= ~(1 << 5);
    }

    user_control |= 2;
    write({USER_CTRL, user_control});
    usleep(100000);
    //cout << "user_control: " << bitset<8>(user_control) << endl;

    write({INT_PIN_CFG, 0x82});
    usleep(100000);
}

void MPU9250::setGyroConfigScale(GyroScale gyroScale)
{
    unsigned char gyro_conf = readValue<unsigned char>(GYRO_CONFIG);
    gyro_conf |= (static_cast<unsigned char>(gyroScale) << 3);
    write({GYRO_CONFIG, gyro_conf});
    activeGyroScale = gyroScale;
}

void MPU9250::setAccelConfigScale(AccelScale accelScale)
{
    unsigned char accel_conf = readValue<unsigned char>(ACCEL_CONFIG);
    accel_conf |= (static_cast<unsigned char>(accelScale) << 3);
    write({ACCEL_CONFIG, accel_conf});
    activeAccelScale = accelScale;
}

int MPU9250::getGyroSensitivity()
{
    switch (activeGyroScale) {
        case GyroScale::_250dps:
            return 131;//131.072
        case GyroScale::_500dps:
            return 66; //65.536
        case GyroScale::_1000dps:
            return 33; //32.768
        case GyroScale::_2000dps:
            return 16; //16.384
        default:
            return 33;
    }
}

int MPU9250::getAccelSensitivity()
{
    switch (activeAccelScale) {
        case AccelScale::_2g:
            return 16384;
        case AccelScale::_4g:
            return 8192;
        case AccelScale::_8g:
            return 4096;
        case AccelScale::_16g:
            return 2048;
        default:
            return 4096;
    }
}
