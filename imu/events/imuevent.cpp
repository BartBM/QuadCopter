#include "imuevent.h"

ImuEvent::ImuEvent()
{

}

ImuEvent::~ImuEvent()
{

}

void ImuEvent::setData(Vector3<float> gyro, Vector3<float> accel)
{
    this->gyro = gyro;
    this->accel = accel;
}

void ImuEvent::setData(Vector3<float> gyro, Vector3<float> accel, Vector3<float> mag)
{
    this->gyro = gyro;
    this->accel = accel;
    this->mag = mag;
}

EventType ImuEvent::getEventType()
{
    return EventType::IMU;
}
