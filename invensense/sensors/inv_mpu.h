#ifndef _INV_MPU_H_
#define _INV_MPU_H_

#include "../communication/i2c/i2cdatabus.h"
#include "../communication/i2c/i2cchip.h"
#include "../math/vector3.h"

#define MPU9250_WRITE_ADDR  0xD0
#define MPU9250_READ_ADDR   0xD1

#define MPU6500

#define AK89xx_SECONDARY
#define AK8963_SECONDARY
#define SUPPORTS_AK89xx_HIGH_SENS   (0x10)
#define AK89xx_FSR                  (4915)

#define INV_X_GYRO      (0x40)
#define INV_Y_GYRO      (0x20)
#define INV_Z_GYRO      (0x10)
#define INV_XYZ_GYRO    (INV_X_GYRO | INV_Y_GYRO | INV_Z_GYRO)
#define INV_XYZ_ACCEL   (0x08)
#define INV_XYZ_COMPASS (0x01)

struct int_param_s {
};

#define MPU_INT_STATUS_DATA_READY       (0x0001)
#define MPU_INT_STATUS_DMP              (0x0002)
#define MPU_INT_STATUS_PLL_READY        (0x0004)
#define MPU_INT_STATUS_I2C_MST          (0x0008)
#define MPU_INT_STATUS_FIFO_OVERFLOW    (0x0010)
#define MPU_INT_STATUS_ZMOT             (0x0020)
#define MPU_INT_STATUS_MOT              (0x0040)
#define MPU_INT_STATUS_FREE_FALL        (0x0080)
#define MPU_INT_STATUS_DMP_0            (0x0100)
#define MPU_INT_STATUS_DMP_1            (0x0200)
#define MPU_INT_STATUS_DMP_2            (0x0400)
#define MPU_INT_STATUS_DMP_3            (0x0800)
#define MPU_INT_STATUS_DMP_4            (0x1000)
#define MPU_INT_STATUS_DMP_5            (0x2000)

/* When entering motion interrupt mode, the driver keeps track of the
 * previous state so that it can be restored at a later time.
 * TODO: This is tacky. Fix it.
 */
struct motion_int_cache_s {
    unsigned short gyro_fsr;
    unsigned char accel_fsr;
    unsigned short lpf;
    unsigned short sample_rate;
    unsigned char sensors_on;
    unsigned char fifo_sensors;
    unsigned char dmp_on;
};

/* Hardware registers needed by driver. */
struct gyro_reg_s {
    unsigned char who_am_i;
    unsigned char rate_div;
    unsigned char lpf;
    unsigned char prod_id;
    unsigned char user_ctrl;
    unsigned char fifo_en;
    unsigned char gyro_cfg;
    unsigned char accel_cfg;
    unsigned char accel_cfg2;
    unsigned char lp_accel_odr;
    unsigned char motion_thr;
    unsigned char motion_dur;
    unsigned char fifo_count_h;
    unsigned char fifo_r_w;
    unsigned char raw_gyro;
    unsigned char raw_accel;
    unsigned char temp;
    unsigned char int_enable;
    unsigned char dmp_int_status;
    unsigned char int_status;
    unsigned char accel_intel;
    unsigned char pwr_mgmt_1;
    unsigned char pwr_mgmt_2;
    unsigned char int_pin_cfg;
    unsigned char mem_r_w;
    unsigned char accel_offs;
    unsigned char i2c_mst;
    unsigned char bank_sel;
    unsigned char mem_start_addr;
    unsigned char prgm_start_h;
#if defined AK89xx_SECONDARY
    unsigned char raw_compass;
    unsigned char s0_addr;
    unsigned char s0_reg;
    unsigned char s0_ctrl;
    unsigned char s1_addr;
    unsigned char s1_reg;
    unsigned char s1_ctrl;
    unsigned char s4_ctrl;
    unsigned char s0_do;
    unsigned char s1_do;
    unsigned char i2c_delay_ctrl;
    /* The I2C_MST_VDDIO bit is in this register. */
    unsigned char yg_offs_tc;
#endif
};

/* Information specific to a particular device. */
struct hw_s {
    unsigned char addr;
    unsigned short max_fifo;
    unsigned char num_reg;
    unsigned short temp_sens;
    short temp_offset;
    unsigned short bank_size;
#if defined AK89xx_SECONDARY
    unsigned short compass_fsr;
#endif
};

/* Cached chip configuration data.
 * TODO: A lot of these can be handled with a bitmask.
 */
struct chip_cfg_s {
    /* Matches gyro_cfg >> 3 & 0x03 */
    unsigned char gyro_fsr;
    /* Matches accel_cfg >> 3 & 0x03 */
    unsigned char accel_fsr;
    /* Enabled sensors. Uses same masks as fifo_en, NOT pwr_mgmt_2. */
    unsigned char sensors;
    /* Matches config register. */
    unsigned char lpf;
    unsigned char clk_src;
    /* Sample rate, NOT rate divider. */
    unsigned short sample_rate;
    /* Matches fifo_en register. */
    unsigned char fifo_enable;
    /* Matches int enable register. */
    unsigned char int_enable;
    /* 1 if devices on auxiliary I2C bus appear on the primary. */
    unsigned char bypass_mode;
    /* 1 if half-sensitivity.
     * NOTE: This doesn't belong here, but everything else in hw_s is const,
     * and this allows us to save some precious RAM.
     */
    unsigned char accel_half;
    /* 1 if device in low-power accel-only mode. */
    unsigned char lp_accel_mode;
    /* 1 if interrupts are only triggered on motion events. */
    unsigned char int_motion_only;
    struct motion_int_cache_s cache;
    /* 1 for active low interrupts. */
    unsigned char active_low_int;
    /* 1 for latched interrupts. */
    unsigned char latched_int;
    /* 1 if DMP is enabled. */
    unsigned char dmp_on;
    /* Ensures that DMP will only be loaded once. */
    unsigned char dmp_loaded;
    /* Sampling rate used when DMP is enabled. */
    unsigned short dmp_sample_rate;
#ifdef AK89xx_SECONDARY
    /* Compass sample rate. */
    unsigned short compass_sample_rate;
    unsigned char compass_addr;
    short mag_sens_adj[3];
#endif
};

/* Information for self-test. */
struct test_s {
    unsigned long gyro_sens;
    unsigned long accel_sens;
    unsigned char reg_rate_div;
    unsigned char reg_lpf;
    unsigned char reg_gyro_fsr;
    unsigned char reg_accel_fsr;
    unsigned short wait_ms;
    unsigned char packet_thresh;
    float min_dps;
    float max_dps;
    float max_gyro_var;
    float min_g;
    float max_g;
    float max_accel_var;
    float max_g_offset;
    unsigned short sample_wait_ms;
};

/* Gyro driver state variables. */
struct gyro_state_s {
    const struct gyro_reg_s *reg;
    const struct hw_s *hw;
    struct chip_cfg_s chip_cfg;
    const struct test_s *test;
};


const struct gyro_reg_s reg = {
    .who_am_i       = 0x75,
    .rate_div       = 0x19,
    .lpf            = 0x1A,
    .prod_id        = 0x0C,
    .user_ctrl      = 0x6A,
    .fifo_en        = 0x23,
    .gyro_cfg       = 0x1B,
    .accel_cfg      = 0x1C,
    .accel_cfg2     = 0x1D,
    .lp_accel_odr   = 0x1E,
    .motion_thr     = 0x1F,
    .motion_dur     = 0x20,
    .fifo_count_h   = 0x72,
    .fifo_r_w       = 0x74,
    .raw_gyro       = 0x43,
    .raw_accel      = 0x3B,
    .temp           = 0x41,
    .int_enable     = 0x38,
    .dmp_int_status = 0x39,
    .int_status     = 0x3A,
    .accel_intel    = 0x69,
    .pwr_mgmt_1     = 0x6B,
    .pwr_mgmt_2     = 0x6C,
    .int_pin_cfg    = 0x37,
    .mem_r_w        = 0x6F,
    .accel_offs     = 0x77,
    .i2c_mst        = 0x24,
    .bank_sel       = 0x6D,
    .mem_start_addr = 0x6E,
    .prgm_start_h   = 0x70
#ifdef AK89xx_SECONDARY
    ,.raw_compass   = 0x49,
    .s0_addr        = 0x25,
    .s0_reg         = 0x26,
    .s0_ctrl        = 0x27,
    .s1_addr        = 0x28,
    .s1_reg         = 0x29,
    .s1_ctrl        = 0x2A,
    .s4_ctrl        = 0x34,
    .s0_do          = 0x63,
    .s1_do          = 0x64,
    .i2c_delay_ctrl = 0x67
#endif
};
const struct hw_s hw = {
    0x68,
    1024,
    128,
    321,
    0,
    256
#ifdef AK89xx_SECONDARY
    ,AK89xx_FSR
#endif
};

const struct test_s test = {
    32768/250,
    32768/2,  //FSR = +-2G = 16384 LSB/G
    0,    /* 1kHz. */
    2,    /* 92Hz low pass filter*/
    0,    /* 250dps. */
    0x0,  /* Accel FSR setting = 2g. */
    200,   //200ms stabilization time
    200,    /* 200 samples */
    20.f,  //20 dps for Gyro Criteria C
    60.f, //Must exceed 60 dps threshold for Gyro Criteria B
    .5f, //Must exceed +50% variation for Gyro Criteria A
    .225f, //Accel must exceed Min 225 mg for Criteria B
    .675f, //Accel cannot exceed Max 675 mg for Criteria B
    .5f,  //Accel must be within 50% variation for Criteria A
    .5f,   //500 mg for Accel Criteria C
    10    //10ms sample time wait
};


class InvMpu : public I2CChip
{
public:
    InvMpu();
    void init(I2CDataBus *i2cDataBus);

    unsigned char getReadAddr() { return MPU9250_READ_ADDR; }
    unsigned char getWriteAddr() { return MPU9250_WRITE_ADDR; }

    int i2c_write(unsigned char write_addr, unsigned char reg_addr, int numberOfBytes, unsigned char* data);
    int i2c_read(unsigned char write_addr, unsigned char reg_addr, int numberOfBytes, unsigned char* data);
    int set_int_enable(unsigned char enable);
    int delay_ms(int ms);

    int get_st_biases(long *gyro, long *accel, unsigned char hw_test);
    int get_st_6500_biases(long *gyro, long *accel, unsigned char hw_test, int debug);
    int accel_6500_self_test(long *bias_regular, long *bias_st, int debug);
    int gyro_6500_self_test(long *bias_regular, long *bias_st, int debug);
    int mpu_read_6500_gyro_bias(long *gyro_bias);

    /* Set up APIs */
    int mpu_init(struct int_param_s *int_param);
    int mpu_init_slave(void);
    int mpu_set_bypass(unsigned char bypass_on);

    /* Configuration APIs */
    int mpu_lp_accel_mode(unsigned short rate);
    int mpu_lp_motion_interrupt(unsigned short thresh, unsigned char time,
        unsigned short lpa_freq);
    int mpu_set_int_level(unsigned char active_low);
    int mpu_set_int_latched(unsigned char enable);

    int mpu_set_dmp_state(unsigned char enable);
    int mpu_get_dmp_state(unsigned char *enabled);

    int mpu_get_lpf(unsigned short *lpf);
    int mpu_set_lpf(unsigned short lpf);

    int mpu_get_gyro_fsr(unsigned short *fsr);
    int mpu_set_gyro_fsr(unsigned short fsr);

    int mpu_get_accel_fsr(unsigned char *fsr);
    int mpu_set_accel_fsr(unsigned char fsr);

    int setup_compass(void);
    int compass_self_test(void);
    int mpu_get_compass_fsr(unsigned short *fsr);

    int mpu_get_gyro_sens(float *sens);
    int mpu_get_accel_sens(unsigned short *sens);

    int mpu_get_sample_rate(unsigned short *rate);
    int mpu_set_sample_rate(unsigned short rate);
    int mpu_get_compass_sample_rate(unsigned short *rate);
    int mpu_set_compass_sample_rate(unsigned short rate);

    int mpu_get_fifo_config(unsigned char *sensors);
    int mpu_configure_fifo(unsigned char sensors);

    int mpu_get_power_state(unsigned char *power_on);
    int mpu_set_sensors(unsigned char sensors);

    int mpu_read_6500_accel_bias(long *accel_bias);
    int mpu_set_gyro_bias_reg(long * gyro_bias);
    int mpu_set_accel_bias_6500_reg(const long *accel_bias);
    int mpu_read_6050_accel_bias(long *accel_bias);
    int mpu_set_accel_bias_6050_reg(const long *accel_bias);

    /* Data getter/setter APIs */
    int mpu_get_gyro_reg(short *data, unsigned long *timestamp);
    int mpu_get_accel_reg(short *data, unsigned long *timestamp);
    int mpu_get_compass_reg(short *data, unsigned long *timestamp);
    int mpu_get_temperature(long *data, unsigned long *timestamp);

    int mpu_get_int_status(short *status);
    int mpu_read_fifo(short *gyro, short *accel, unsigned long *timestamp,
        unsigned char *sensors, unsigned char *more);
    int mpu_read_fifo_stream(unsigned short length, unsigned char *data,
        unsigned char *more);
    int mpu_reset_fifo(void);

    int mpu_write_mem(unsigned short mem_addr, unsigned short length,
        unsigned char *data);
    int mpu_read_mem(unsigned short mem_addr, unsigned short length,
        unsigned char *data);
    int mpu_load_firmware(unsigned short length, const unsigned char *firmware,
        unsigned short start_addr, unsigned short sample_rate);

    int mpu_reg_dump(void);
    int mpu_read_reg(unsigned char reg, unsigned char *data);
    int mpu_run_self_test(long *gyro, long *accel);
    int mpu_run_6500_self_test(long *gyro, long *accel, unsigned char debug);
    int mpu_register_tap_cb(void (*func)(unsigned char, unsigned char));

private:
    struct gyro_state_s st;
};

#endif  /* #ifndef _INV_MPU_H_ */

