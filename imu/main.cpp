#include <iostream>
#include "communication/buspirate.h"
#include "sensors/variometer.h"
#include "sensors/mpu9250.h"
#include "math/vector3.h"
#include <unistd.h>
#include <bitset>

using namespace std;

void testCompass(AK8963& compass)
{
    compass.setOutputBitSetting(OutputBitSetting::_16BIT);
    compass.setOperationModeSetting(OperationMode::CONT_MEASUREMENT1);
    for (int i=0; i<10; i++) {

        RegStatus1 regStatus1;
        regStatus1 = compass.readStatus1();

        while (!regStatus1.isDataReady()) {
            regStatus1 = compass.readStatus1();
        }

        cout << compass.readRawMeasurementData().toString() << endl;
        if (compass.readStatus2().isMagneticSensorOverflow()) {
            cout << "OVERFLOW!" << endl;
        }
        compass.setOperationModeSetting(OperationMode::SINGLE_MEASUREMENT);

    }
}

void testAccel(MPU9250 imu)
{
    imu.setAccelConfigScale(AccelScale::_8g);
    for (int i=0; i<20; i++) {
        Vector3<short> accelData = imu.readAccel();
        cout << accelData.toString() << endl;
        usleep(10000);
    }
}

void testGyro(MPU9250 imu)
{
    for (int i=0; i<20; i++) {
        Vector3<int> gyroData = imu.readGyro();
        cout << gyroData.toString() << endl;
        usleep(5000);
    }
}

int main(int argc, char *argv[])
{

    BusPirate busPirate;
    busPirate.init();

    MPU9250 imu;
    imu.init(&busPirate);
    imu.whoAmi();
    imu.configure();
    imu.configureCompass();

//    testGyro(imu);
//    imu.calibrateSensors();
//    imu.selfTest();
//    testGyro(imu);

    imu.setSamplerateDivider(20);
    imu.enableFifo(true, true, true);
    imu.setI2CBypass(true);
    imu.readCompass();
    imu.readFifoStream();
    imu.readCompass();

//    imu.configureCompass();
//    AK8963 compass = imu.getCompass();
//    compass.selfTest();
//    testCompass(compass);

    return 0;
}

