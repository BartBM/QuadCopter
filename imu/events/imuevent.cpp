#include "imuevent.h"

ImuEvent::ImuEvent()
{

}

ImuEvent::ImuEvent(const ImuEvent& imuEvent)
{
    this->accel = imuEvent.accel;
    this->gyro = imuEvent.gyro;
    this->mag = imuEvent.mag;
}

ImuEvent& ImuEvent::operator= (const ImuEvent& imuEvent)
{
    this->accel = imuEvent.accel;
    this->gyro = imuEvent.gyro;
    this->mag = imuEvent.mag;
    return *this;
}

ImuEvent::~ImuEvent()
{

}

ImuEvent* ImuEvent::clone()
{
    return new ImuEvent(*this);
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
