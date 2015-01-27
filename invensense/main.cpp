#include <iostream>
#include "communication/buspirate.h"
#include "math/vector3.h"
#include <unistd.h>
#include "sensors/inv_mpu.h"
#include "sensors/inv_dmp.h"
#include <bitset>
#include <math.h>

using namespace std;

void readGyro(InvMpu &invMpu) {
    short data[3] = {0, 0, 0};
    unsigned long timestamp;

    for (int i=0; i<1000; i++) {
        invMpu.mpu_get_gyro_reg(&data[0], &timestamp);
        cout << "gyro data: " << data[0] << ", " << data[1] << ", " << data[2] << endl;
        usleep(10000);
    }
}

void init(InvMpu& mpu, InvDmp& dmp) {
    struct int_param_s int_param;
    printf("MPU init: %i\n", mpu.mpu_init(&int_param));
    printf("MPU sensor init: %i\n", mpu.mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL));
    printf("MPU configure fifo: %i\n", mpu.mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL));
    printf("DMP firmware: %i\n",dmp.dmp_load_motion_driver_firmware());
    //printf("DMP orientation: %i\n ",dmp.dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)));

    unsigned short dmp_features = DMP_FEATURE_6X_LP_QUAT /* | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL*/;
    printf("DMP feature enable: %i\n", dmp.dmp_enable_feature(dmp_features));
    printf("DMP set fifo rate: %i\n", dmp.dmp_set_fifo_rate(100));
    printf("DMP enable %i\n", mpu.mpu_set_dmp_state(1));
}

void readDmpFifo(InvMpu& mpu, InvDmp& dmp) {
    short gyro[3] = {0, 0, 0};
    short accel[3];
    short sensors[3];
    long quaternion[4];
    unsigned long timestamp;
    unsigned char more;
    unsigned char previousMore = (int) 0;
    int sleeptime = 1000;

    for (int i=0; i<10000; i++) {
        int status = dmp.dmp_read_fifo(&gyro[0], &accel[0], &quaternion[0], &timestamp, &sensors[0], &more);
        if (status != 0) {
            usleep(100);
            continue;
        }
        //cout << "dmp gyro: " << gyro[0] << ", " << gyro[1] << ", " << gyro[2] << endl;
        //cout << "dmp accel: " << accel[0] << ", " << accel[1] << ", " << accel[2] << endl;
        //cout << "quaternion: " << quat[0] << ", " << quat[1] << ", " << quat[2] << ", " << quat[3] << endl;

            double w = (float) (quaternion[0]>>16) / 16384.0f;
            double x = (float) (quaternion[1]>>16) / 16384.0f;
            double y = (float) (quaternion[2]>>16) / 16384.0f;
            double z = (float) (quaternion[3]>>16) / 16384.0f;

            double sqw = w*w;
            double sqx = x*x;
            double sqy = y*y;
            double sqz = z*z;

            float Z = atan2(2.0 * (x*y + z*w),(sqx - sqy - sqz + sqw)) * (180.0f/3.1415f);
            float X = atan2(2.0 * (y*z + x*w),(-sqx - sqy + sqz + sqw)) * (180.0f/3.1415f);
            float Y = asin(-2.0 * (x*z - y*w)) * (180.0f/3.1415f);

            if (i%5 == 0) {
                //cout << (-2.0 * (x*z - y*w)) << "\t" << asin(-2.0 * (x*z - y*w)) * (180.0f/3.1415f) << endl;
                cout << "x, y, z (" << X << ", " << Y << ", " << Z << ")" << " - packets: " << (int) more << endl;
            }

            if ((int) more > 10) {
                sleeptime-= 100;
            } else if ((int) more < 10) {
                sleeptime+=100;
            }

            if (sleeptime<0) {
                sleeptime = 0;
            }

        usleep(sleeptime);
    }
    cout << "!!!!!!!!!!!   finito" << endl;
}

int main(int argc, char *argv[])
{
    BusPirate busPirate;
    busPirate.init();

    int_param_s params;

    InvMpu mpu;
    mpu.init(&busPirate);
    //mpu.setup_compass();

    //InvDmp dmp(&mpu);
    //dmp.init(&busPirate);

    mpu.mpu_init(&params);
    mpu.mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);

    /*
    long gyro[3] = {0, 0, 0};
    long gyro_factory_bias[3] = {0, 0, 0};
    long accel[3] = {0, 0, 0};
    unsigned char hw_test = 0;
    int debug = 0;

    mpu.mpu_read_6500_gyro_bias(&gyro_factory_bias[0]);
    cout << "factory bias: " << gyro_factory_bias[0] << ", " << gyro_factory_bias[1] << ", " << gyro_factory_bias[2] << endl;

    float sensitivity;
    mpu.mpu_get_gyro_sens(&sensitivity);
    cout << "sensitivity: " << sensitivity << endl;

    int selfTestStatus = mpu.mpu_run_6500_self_test(&gyro[0], &accel[0], debug);
    cout << "self test status: " << bitset<8>(selfTestStatus) << endl;
    cout << "mpu_run_6500_self_test gyro: " << gyro[0] << ", " << gyro[1] << ", " << gyro[2] << endl;
    */

    //init(mpu, dmp);

    //readDmpFifo(mpu, dmp);

    return 0;

}

