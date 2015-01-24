#include "mpu9250.h"
#include <stdexcept>
#include <unistd.h>
#include <iostream>
#include <bitset>

using namespace std;

MPU9250::MPU9250() : I2CChip()
{
    cout << endl << "==> MPU 9250" << endl;
}

MPU9250::~MPU9250()
{

}

void MPU9250::init(I2CDataBus *i2cDataBus)
{
    I2CChip::init(i2cDataBus);
    ak8963.init(i2cDataBus);
}

void MPU9250::configure()
{
    write({PWR_MGMT_01,     0x00}); //disable sleep mode
    usleep(200000);
    //write({PWR_MGMT_01,     0x80}); //reset
    //usleep(100000);
    write({PWR_MGMT_01,     0x01}); //select accel x as time source

    write({CONFIG,          0x03});
    write({PWR_MGMT_02,     0x00});

    write({SMPLRT_DIV,      0x04});
    write({GYRO_CONFIG,     0b00011000});
    write({ACCEL_CONFIG,    0b00011000});
    write({ACCEL_CONFIG2,   0b00001011});
    usleep(100000);

    write({INT_PIN_CFG,     0x22});
    write({INT_ENABLE,      0x00});
    write({FIFO_EN,         0x00});
    usleep(100000);
}

void MPU9250::configureCompass()
{
    write({PWR_MGMT_01,     0x80}); //reset
    usleep(100000);

    write({PWR_MGMT_01,     0x01}); //disable sleep

    cout << "go bypass" << endl;
    setI2CBypass(true);
    ak8963.configure();
}

void MPU9250::calibrateSensors()
{
    cout << "[MPU9250 calibrateSensors]" << endl;
    readBiases();
    calibrateGyro();
    calibrateAccel();
}

void MPU9250::readBiases()
{
    cout << "[MPU9250 readBiases]" << endl;
    write({PWR_MGMT_01,     0x80});
    usleep(100000);

    write({PWR_MGMT_01,     0x01});
    write({PWR_MGMT_02,     0x00});
    usleep(100000);

    write({INT_ENABLE,      0x00});
    write({FIFO_EN,         0x00});
    write({PWR_MGMT_01,     0x00});
    write({I2C_MST_CTRL,    0x00});
    write({USER_CTRL,       0x00});
    write({USER_CTRL,       0x0C}); // DMP_RST & FIFO_RST
    usleep(15000);

    write({CONFIG,          0x02});
    write({SMPLRT_DIV,      0x00});
    write({GYRO_CONFIG,     0x00});
    write({ACCEL_CONFIG,    0x00});
    usleep(200000);

    //write({GYRO_CONFIG,     0b00011000});
    //write({ACCEL_CONFIG,    0b00011000});
    //write({ACCEL_CONFIG2,   0b00001011});

    write({USER_CTRL,       0x40}); // enable FIFO
    usleep(100000);

    write({FIFO_EN,         0x70}); // enable gyro & accel (except for temp)
    usleep(15000);
    write({FIFO_EN,         0x00});

    int fifo_counter = ((short) readValue<unsigned char>(FIFO_COUNTH)) << 8 | readValue<unsigned char>(FIFO_COUNTL);
    int packet_counter = fifo_counter / 12;

    cout << "\tNr of packets: " << dec << packet_counter << endl;

    for (int i=0; i<packet_counter; i++) {
        vector<unsigned char> data = readValues<unsigned char>(FIFO_R_W, 6);

        vec3_accel_bias.setX((((short) data[0] << 8) | data[1]));
        vec3_accel_bias.setY((((short) data[2] << 8) | data[3]));
        vec3_accel_bias.setZ((((short) data[4] << 8) | data[5]));

        vec3_gyr_bias.setX(vec3_gyr_bias.getX() + (((short) data[6])  << 8 | data[7]));
        vec3_gyr_bias.setY(vec3_gyr_bias.getY() + (((short) data[8])  << 8 | data[9]));
        vec3_gyr_bias.setZ(vec3_gyr_bias.getZ() + (((short) data[10]) << 8 | data[11]));
    }

    vec3_accel_bias.setX((long) ((((long long) vec3_accel_bias.getX()) << 16) / ACCEL_SENSITIVITY / packet_counter));
    vec3_accel_bias.setY((long) ((((long long) vec3_accel_bias.getY()) << 16) / ACCEL_SENSITIVITY / packet_counter));
    vec3_accel_bias.setZ((long) ((((long long) vec3_accel_bias.getZ()) << 16) / ACCEL_SENSITIVITY / packet_counter));

    vec3_gyr_bias.setX((long) ((((long long) vec3_gyr_bias.getX()) << 16) / GYRO_SENSITIVITY / packet_counter));
    vec3_gyr_bias.setY((long) ((((long long) vec3_gyr_bias.getY()) << 16) / GYRO_SENSITIVITY / packet_counter));
    vec3_gyr_bias.setZ((long) ((((long long) vec3_gyr_bias.getZ()) << 16) / GYRO_SENSITIVITY / packet_counter));

    if (vec3_accel_bias.getZ() > 0L)
            vec3_accel_bias.setZ(vec3_accel_bias.getZ() - 65536L);
        else
            vec3_accel_bias.setZ(vec3_accel_bias.getZ() + 65536L);

    cout << "\tAccel bias: " << vec3_accel_bias.toString() << endl;
    cout << "\tGyro bias: " << vec3_gyr_bias.toString() << endl;

}

void MPU9250::calibrateGyro()
{
    cout << "[MPU9250 calibrateGyro]" << endl;
    write({XG_OFFSET_H, static_cast<unsigned char>(((vec3_gyr_bias.getX() * -1) >> 8) & 0xFF) });
    write({XG_OFFSET_L, static_cast<unsigned char>((vec3_gyr_bias.getX() * -1) & 0xFF) });

    write({YG_OFFSET_H, static_cast<unsigned char>(((vec3_gyr_bias.getY() * -1) >> 8) & 0xFF) });
    write({YG_OFFSET_L, static_cast<unsigned char>((vec3_gyr_bias.getY() * -1) & 0xFF) });

    write({ZG_OFFSET_H, static_cast<unsigned char>(((vec3_gyr_bias.getZ() * -1) >> 8) & 0xFF) });
    write({ZG_OFFSET_L, static_cast<unsigned char>((vec3_gyr_bias.getZ() * -1) & 0xFF) });
}

void MPU9250::calibrateAccel()
{
    cout << "[MPU9250 calibrateAccel]" << endl;
    Vector3<long> vec3_accel_reg_bias;
    vec3_accel_reg_bias.setX(((long) readValue<unsigned char>(XA_OFFSET_H) << 8) | readValue<unsigned char>(XA_OFFSET_L));
    vec3_accel_reg_bias.setY(((long) readValue<unsigned char>(YA_OFFSET_H) << 8) | readValue<unsigned char>(YA_OFFSET_L));
    vec3_accel_reg_bias.setZ(((long) readValue<unsigned char>(ZA_OFFSET_H) << 8) | readValue<unsigned char>(ZA_OFFSET_L));

    vec3_accel_reg_bias -= (vec3_accel_bias & ~1);

    write({XA_OFFSET_H, static_cast<unsigned char>(((vec3_accel_reg_bias.getX() * -1) >> 8) & 0xFF) });
    write({XA_OFFSET_L, static_cast<unsigned char>((vec3_accel_reg_bias.getX() * -1) & 0xFF) });

    write({YA_OFFSET_H, static_cast<unsigned char>(((vec3_accel_reg_bias.getY() * -1) >> 8) & 0xFF) });
    write({YA_OFFSET_L, static_cast<unsigned char>((vec3_accel_reg_bias.getY() * -1) & 0xFF) });

    write({ZA_OFFSET_H, static_cast<unsigned char>(((vec3_accel_reg_bias.getZ() * -1) >> 8) & 0xFF) });
    write({ZA_OFFSET_L, static_cast<unsigned char>((vec3_accel_reg_bias.getZ() * -1) & 0xFF) });
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
