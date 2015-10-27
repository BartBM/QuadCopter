#include <iostream>
#include <iomanip>
#include "eventlogger.h"
#include "imuevent.h"

using namespace std;

EventLogger::EventLogger()
{

}

EventLogger::~EventLogger()
{
    cout << "EventLogger destructor" << endl;
}

void EventLogger::processEvent(Event* event)
{
    if (ImuEvent* imuEvent = dynamic_cast<ImuEvent*>(event)) {
        cout << "IMU gyro (" << fixed << dec << setw(7) << setprecision(2) << setfill(' ') << imuEvent->getGyroscopeReading().getX() << ", " << setw(7) << imuEvent->getGyroscopeReading().getY() << ", " << setw(7) << imuEvent->getGyroscopeReading().getZ() << ")"
             << "\t accel (" << setprecision(4) << setw(7) << imuEvent->getAccelerometerReading().getX() << ", " << setw(7) <<  imuEvent->getAccelerometerReading().getY() << ", " << setw(7) << imuEvent->getAccelerometerReading().getZ() << ")"
             << "\t\t mag (" << setw(7) << imuEvent->getMagnetometerReading().getX() << ", " << setw(7) <<  imuEvent->getMagnetometerReading().getY() << ", " << setw(7) << imuEvent->getMagnetometerReading().getZ() << ")"
             << endl;
    }
}
