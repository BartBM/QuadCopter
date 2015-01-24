#include <iostream>
#include "communication/buspirate.h"
#include "sensors/variometer.h"
#include "sensors/mpu9250.h"
#include "math/vector3.h"
#include <unistd.h>

using namespace std;

void testCompass(AK8963& compass)
{
    compass.setOutputBitSetting(OutputBitSetting::_16BIT);
    compass.setOperationModeSetting(OperationMode::SINGLE_MEASUREMENT);
    for (int i=0; i<200; i++) {

        RegStatus1 regStatus1;
        regStatus1 = compass.readStatus1();

        int counter = 0;
        cout << "counter: ";
        while (!regStatus1.isDataReady()) {
            ++counter;
            cout << dec << counter << " ";
            //usleep(10);
            regStatus1 = compass.readStatus1();
        }
        cout << endl;

        cout << compass.readRawMeasurementData().toString() << endl;
        if (compass.readStatus2().isMagneticSensorOverflow()) {
            cout << "OVERFLOW!" << endl;
        }
        compass.setOperationModeSetting(OperationMode::SINGLE_MEASUREMENT);

    }
}

void testAccel(MPU9250 imu)
{
    for (int i=0; i<20; i++) {
        Vector3<short> accelData = imu.readAccel();
        cout << accelData.toString() << endl;
        usleep(10000);
    }
}

void testGyro(MPU9250 imu)
{
    cout << "testGyro" << endl;
    for (int i=0; i<20; i++) {
        Vector3<int> gyroData = imu.readGyro();
        cout << gyroData.toString() << endl;
        usleep(1000);
    }
}

int main(int argc, char *argv[])
{

    BusPirate busPirate;
    busPirate.init();

    //Variometer variometer;
    //variometer.init(&busPirate);

    MPU9250 imu;
    imu.init(&busPirate);
    imu.whoAmi();
    imu.configure();

    //testGyro(imu);

    //imu.calibrateSensors();
    //imu.configure();

    imu.selfTest();

    //testGyro(imu);
    //testAccel(imu);

    //imu.configureCompass();
    //AK8963 compass = imu.getCompass();
    //testCompass(compass);

    return 0;
}

