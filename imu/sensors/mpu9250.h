#ifndef MPU9250_H
#define MPU9250_H

#include "../communication/i2c/i2cdatabus.h"
#include "../communication/i2c/i2cchip.h"
#include "../math/vector3.h"
#include "mpu9250_constants.h"
#include "ak8963.h"

#define SELF_TEST_SAMPLES 20

enum class GyroScale : unsigned char {
    _250dps = 0b00,
    _500dps = 0b01,
    _1000dps = 0b10,
    _2000dps = 0b11
};

enum class AccelScale : unsigned char {
    _2g = 0b00,
    _4g = 0b01,
    _8g = 0b10,
    _16g = 0b11
};

class MPU9250 : public I2CChip
{
public:
    MPU9250();
    ~MPU9250();
    void init(I2CDataBus *i2cDataBus);

    unsigned char getReadAddr() { return MPU9250_READ_ADDR; }
    unsigned char getWriteAddr() { return MPU9250_WRITE_ADDR; }
    AK8963& getCompass() { return ak8963; }


    void whoAmi();
    void configure();
    void configureCompass();
    void calibrateSensors();
    void selfTest();
    Vector3<short> readGyro();
    Vector3<short> readAccel();

    void setGyroSelfTest(bool enabled);
    void setAccelSelfTest(bool enabled);
    void setI2CBypass(bool enabled);

private:
    void readBiases();
    void calibrateGyro();
    void calibrateAccel();

    Vector3<int>  gyroSelfTest,  accelSelfTest;
    Vector3<long> vec3_gyr_bias, vec3_accel_bias;

    AK8963 ak8963;
};

#endif // MPU9250_H
