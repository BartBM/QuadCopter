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



//const struct test_s test = {
//    .gyro_sens      = 32768/250,
//    .accel_sens     = 32768/2,  //FSR = +-2G = 16384 LSB/G
//    .reg_rate_div   = 0,    /* 1kHz. */
//    .reg_lpf        = 2,    /* 92Hz low pass filter*/
//    .reg_gyro_fsr   = 0,    /* 250dps. */
//    .reg_accel_fsr  = 0x0,  /* Accel FSR setting = 2g. */
//    .wait_ms        = 200,   //200ms stabilization time
//    .packet_thresh  = 200,    /* 200 samples */
//    .min_dps        = 20.f,  //20 dps for Gyro Criteria C
//    .max_dps        = 60.f, //Must exceed 60 dps threshold for Gyro Criteria B
//    .max_gyro_var   = .5f, //Must exceed +50% variation for Gyro Criteria A
//    .min_g          = .225f, //Accel must exceed Min 225 mg for Criteria B
//    .max_g          = .675f, //Accel cannot exceed Max 675 mg for Criteria B
//    .max_accel_var  = .5f,  //Accel must be within 50% variation for Criteria A
//    .max_g_offset   = .5f,   //500 mg for Accel Criteria C
//    .sample_wait_ms = 10    //10ms sample time wait
//};

//const struct gyro_reg_s reg = {
//    .who_am_i       = 0x75,
//    .rate_div       = 0x19,
//    .lpf            = 0x1A,
//    .prod_id        = 0x0C,
//    .user_ctrl      = 0x6A,
//    .fifo_en        = 0x23,
//    .gyro_cfg       = 0x1B,
//    .accel_cfg      = 0x1C,
//    .accel_cfg2     = 0x1D,
//    .lp_accel_odr   = 0x1E,
//    .motion_thr     = 0x1F,
//    .motion_dur     = 0x20,
//    .fifo_count_h   = 0x72,
//    .fifo_r_w       = 0x74,
//    .raw_gyro       = 0x43,
//    .raw_accel      = 0x3B,
//    .temp           = 0x41,
//    .int_enable     = 0x38,
//    .dmp_int_status = 0x39,
//    .int_status     = 0x3A,
//    .accel_intel    = 0x69,
//    .pwr_mgmt_1     = 0x6B,
//    .pwr_mgmt_2     = 0x6C,
//    .int_pin_cfg    = 0x37,
//    .mem_r_w        = 0x6F,
//    .accel_offs     = 0x77,
//    .i2c_mst        = 0x24,
//    .bank_sel       = 0x6D,
//    .mem_start_addr = 0x6E,
//    .prgm_start_h   = 0x70
//#ifdef AK89xx_SECONDARY
//    ,.raw_compass   = 0x49,
//    .s0_addr        = 0x25,
//    .s0_reg         = 0x26,
//    .s0_ctrl        = 0x27,
//    .s1_addr        = 0x28,
//    .s1_reg         = 0x29,
//    .s1_ctrl        = 0x2A,
//    .s4_ctrl        = 0x34,
//    .s0_do          = 0x63,
//    .s1_do          = 0x64,
//    .i2c_delay_ctrl = 0x67
//#endif
//};


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

//        vec3_accel_bias.setX((((short) data[0] << 8) | data[1]));
//        vec3_accel_bias.setY((((short) data[2] << 8) | data[3]));
//        vec3_accel_bias.setZ((((short) data[4] << 8) | data[5]));
        //cout << vec3_accel_bias.toString() << endl;

//        vec3_gyr_bias.setX(vec3_gyr_bias.getX() + (((short) data[6])  << 8 | data[7]));
//        vec3_gyr_bias.setY(vec3_gyr_bias.getY() + (((short) data[8])  << 8 | data[9]));
//        vec3_gyr_bias.setZ(vec3_gyr_bias.getZ() + (((short) data[10]) << 8 | data[11]));

        vec3_gyr_bias.setX(vec3_gyr_bias.getX() + (((short) data[0]) << 8 | data[1]));
        vec3_gyr_bias.setY(vec3_gyr_bias.getY() + (((short) data[2]) << 8 | data[3]));
        vec3_gyr_bias.setZ(vec3_gyr_bias.getZ() + (((short) data[4]) << 8 | data[5]));
        cout << "gyr bias: " << vec3_gyr_bias.toString() << endl;
    }

    //vec3_accel_bias.setX((long) ((((long long) vec3_accel_bias.getX()) << 16) / ACCEL_SENSITIVITY / packet_counter));
    //vec3_accel_bias.setY((long) ((((long long) vec3_accel_bias.getY()) << 16) / ACCEL_SENSITIVITY / packet_counter));
    //vec3_accel_bias.setZ((long) ((((long long) vec3_accel_bias.getZ()) << 16) / ACCEL_SENSITIVITY / packet_counter));

    //vec3_gyr_bias.setX((long) vec3_gyr_bias.getX()  /*/ GYRO_SENSITIVITY */ / packet_counter);
    //vec3_gyr_bias.setY((long) vec3_gyr_bias.getY()  /*/ GYRO_SENSITIVITY */ / packet_counter);
    //vec3_gyr_bias.setZ((long) vec3_gyr_bias.getZ()  /*/ GYRO_SENSITIVITY */ / packet_counter);
    vec3_gyr_bias.setX((long) ((((long long) vec3_gyr_bias.getX()) << 16) / GYRO_SENSITIVITY / packet_counter));
    vec3_gyr_bias.setY((long) ((((long long) vec3_gyr_bias.getY()) << 16) / GYRO_SENSITIVITY / packet_counter));
    vec3_gyr_bias.setZ((long) ((((long long) vec3_gyr_bias.getZ()) << 16) / GYRO_SENSITIVITY / packet_counter));
    //vec3_gyr_bias.setX(50);

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
