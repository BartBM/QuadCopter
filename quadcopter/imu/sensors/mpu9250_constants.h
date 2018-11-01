#ifndef MPU9250_CONSTANTS_H
#define MPU9250_CONSTANTS_H

#define MPU9250_WRITE_ADDR  0xD0
#define MPU9250_READ_ADDR   0xD1

#define GYRO_SENSITIVITY    131
#define ACCEL_SENSITIVITY   16384

#define SMPLRT_DIV          0x19
#define CONFIG              0x1A
#define GYRO_CONFIG         0x1B
#define ACCEL_CONFIG        0x1C
#define ACCEL_CONFIG2       0x1D
#define FIFO_EN             0x23
#define I2C_MST_CTRL        0x24

#define SELF_TEST_X_GYRO    0x01
#define SELF_TEST_Y_GYRO    0x02
#define SELF_TEST_Z_GYRO    0x03
#define SELF_TEST_X_ACCEL   0x0D
#define SELF_TEST_Y_ACCEL   0x0E
#define SELF_TEST_Z_ACCEL   0x0F

#define XG_OFFSET_H         0x13
#define XG_OFFSET_L         0x14
#define YG_OFFSET_H         0x15
#define YG_OFFSET_L         0x16
#define ZG_OFFSET_H         0x17
#define ZG_OFFSET_L         0x18

#define I2C_SLV0_ADDR       0x25
#define I2C_SLV0_REG        0x26
#define I2C_SLV0_CTRL       0x27

#define I2C_SLV1_ADDR       0x28
#define I2C_SLV1_REG        0x29
#define I2C_SLV1_CTRL       0x2A

#define I2C_SLV4_CTRL       0x34
#define INT_PIN_CFG         0x37
#define INT_ENABLE          0x38

#define ACCEL_XOUT_H        0x3B
#define ACCEL_XOUT_L        0x3C
#define ACCEL_YOUT_H        0x3D
#define ACCEL_YOUT_L        0x3E
#define ACCEL_ZOUT_H        0x3F
#define ACCEL_ZOUT_L        0x40
#define TEMP_OUT_H          0x41
#define TEMP_OUT_L          0x42
#define GYRO_XOUT_H         0x43
#define GYRO_XOUT_L         0x44
#define GYRO_YOUT_H         0x45
#define GYRO_YOUT_L         0x46
#define GYRO_ZOUT_H         0x47
#define GYRO_ZOUT_L         0x48

#define EXT_SENS_DATA_00    0x49

#define I2C_SLV0_DO         0x63
#define I2C_SLV1_DO         0x64
#define I2C_SLV2_DO         0x65
#define I2C_SLV3_DO         0x66

#define USER_CTRL           0x6A
#define PWR_MGMT_01         0x6B
#define PWR_MGMT_02         0x6C
#define I2C_MST_DELAY_CTRL  0x67

#define FIFO_COUNTH         0x72
#define FIFO_COUNTL         0x73
#define FIFO_R_W            0x74

#define XA_OFFSET_H         0x77
#define XA_OFFSET_L         0x78
#define YA_OFFSET_H         0x7A
#define YA_OFFSET_L         0x7B
#define ZA_OFFSET_H         0x7D
#define ZA_OFFSET_L         0x7E

#endif // MPU9250_CONSTANTS_H

