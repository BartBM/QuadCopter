#ifndef IMUEVENT_H
#define IMUEVENT_H

#include "../math/vector3.h"
#include "event.h"

class ImuEvent : public Event
{
public:
    ImuEvent();
    ImuEvent(const ImuEvent& imuEvent);
    ImuEvent& operator= (const ImuEvent& m);
    ~ImuEvent();

    void setData(Vector3<float> gyro, Vector3<float> accel);
    void setData(Vector3<float> gyro, Vector3<float> accel, Vector3<float> mag);
    EventType getEventType();
    ImuEvent* clone();
    Vector3<float> getAccelerometerReading() { return accel; }
    Vector3<float> getGyroscopeReading() { return gyro; }
    Vector3<float> getMagnetometerReading() { return mag; }

private:
    Vector3<float> gyro, accel, mag;
};

#endif // IMUEVENT_H
