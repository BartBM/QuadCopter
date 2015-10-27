#include <bitset>
#include <iostream>
#include <unistd.h>
#include <cmath>
#include "communication/buspirate.h"
#include "events/eventlogger.h"
#include "math/vector3.h"
#include "math/sensorfusion.h"
#include "sensors/mpu9250.h"
#include "sensors/variometer.h"

using namespace std;

#define PI 3.14159265359

double minX = 100.0;
double minY = 100.0;
double minZ = 100.0;
double maxX = -100.0;
double maxY = -100.0;
double maxZ = -100.0;
double deltaMax = 0.0;
double deltaX = 0.0;
double deltaY = 0.0;
double deltaZ = 0.0;
bool corrected = false;

void calculateHeading(Vector3<double>* mag)
{
    // http://stackoverflow.com/questions/1055014/getting-magnetic-north-from-a-xyz-magnetometer-iphone-3-0
    double heading;

    //mag->setX(mag->getX() + 10);
    //mag->setY(mag->getY() - 19);
    //mag->setZ(mag->getZ() + 17);



    if (corrected) {
        mag->setX((mag->getX() - ((maxX + minX) /2.0f)) * deltaX);
        mag->setY((mag->getY() - ((maxY + minY) /2.0f)) * deltaY);
        mag->setZ((mag->getZ() - ((maxZ + minZ) /2.0f)) * deltaZ);
    } else {
        if (mag->getX() < minX) minX = mag->getX();
        if (mag->getY() < minY) minY = mag->getY();
        if (mag->getZ() < minZ) minZ = mag->getZ();
        if (mag->getX() > maxX) maxX = mag->getX();
        if (mag->getY() > maxY) maxY = mag->getY();
        if (mag->getZ() > maxZ) maxZ = mag->getZ();
    }

    cout << "corrected: " << mag->toString() << endl;

//    double temp = -mag->getX();
//    mag->setX(mag->getY());
//    mag->setY(temp);

    /*
    if (mag->getY() > 0.0f) {
        heading = 90 - atan2(mag->getX(), mag->getY()) * 180 / PI;
    } else if (mag->getY() < 0.0f) {
        heading = 270 - atan2(mag->getX(), mag->getY()) * 180 / PI;
    } else if (mag->getY() == 0.0f && mag->getX()) {
        heading = 180;
    } else {
        heading = 0;
    }
*/

    cout << "Heading = " << atan2(mag->getX(), mag->getY()) * 180 / PI << endl;
}

void testCompass(AK8963& compass, int mag_samples)
{
    compass.setOutputBitSetting(OutputBitSetting::_14BIT);
    //compass.setOperationModeSetting(OperationMode::CONT_MEASUREMENT1);
    for (int i=0; i<mag_samples; i++) {
        compass.setOperationModeSetting(OperationMode::SINGLE_MEASUREMENT);
        RegStatus1 regStatus1;
        regStatus1 = compass.readStatus1();

        while (!regStatus1.isDataReady()) {
            regStatus1 = compass.readStatus1();
        }

        // cout << compass.readRawMeasurementData().toString() << endl;
        Vector3<double> reading = compass.readAdjustedMeasurementData();
        //cout << reading.toString() << endl;
        calculateHeading(&reading);
        if (compass.readStatus2().isMagneticSensorOverflow()) {
            cout << "OVERFLOW!" << endl;
        }
        usleep(100000);


    }
}

void testAccel(MPU9250 imu)
{
    imu.setAccelConfigScale(AccelScale::_8g);
    for (int i=0; i<20; i++) {
        Vector3<short> accelData = imu.readAccel();
        cout << accelData.toString() << endl;
        usleep(100000);
    }
}

void testGyro(MPU9250 imu)
{
    for (int i=0; i<20; i++) {
        Vector3<int> gyroData = imu.readGyro();
        cout << gyroData.toString() << endl;
        usleep(2000);
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

//    imu.configureCompass();

//    testGyro(imu);
//    testAccel(imu);
//    imu.calibrateSensors();
//    imu.selfTest();
//    testGyro(imu);
//    testAccel(imu);

    imu.configureCompass();
    AK8963 compass = imu.getCompass();
    compass.selfTest();
    testCompass(compass, 200);
    corrected = true;
    deltaMax = max(maxX - minX, maxY - minY);
    deltaMax = max(maxZ - minZ, deltaMax);
    deltaX = deltaMax / (maxX - minX);
    deltaY = deltaMax / (maxY - minY);
    deltaZ = deltaMax / (maxZ - minZ);
    cout << "##################################################################" << endl;
    cout << "X:  " << minX << " : " << maxX << endl;
    cout << "Y:  " << minY << " : " << maxY << endl;
    cout << "Z:  " << minZ << " : " << maxZ << endl;
    cout << "dX: " << deltaX << endl;
    cout << "dY: " << deltaY << endl;
    cout << "dZ: " << deltaZ << endl;
    cout << "##################################################################" << endl;
    sleep(10);
    testCompass(compass, 1000);



//    compass.setOutputBitSetting(OutputBitSetting::_14BIT);
//    compass.setOperationModeSetting(OperationMode::CONT_MEASUREMENT1);

//    EventLogger eventLogger;
//    imu.registerObserver(&eventLogger);

//    SensorFusion sensorFusion;
//    imu.registerObserver(&sensorFusion);

//    imu.setSamplerateDivider(11);
//    imu.enableFifo(true, true, false);
//    imu.setI2CBypass(false);
//    imu.readFifoStream();

    return 0;
}

