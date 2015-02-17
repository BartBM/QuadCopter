#ifndef IMUEVENT_H
#define IMUEVENT_H

#include "../math/vector3.h"
#include "event.h"

class ImuEvent : public Event
{
public:
    ImuEvent();
    ~ImuEvent();

    EventType getEventType();
    void setData(Vector3<float> gyro, Vector3<float> accel);
    void setData(Vector3<float> gyro, Vector3<float> accel, Vector3<float> mag);

private:
    Vector3<float> gyro, accel, mag;
};

#endif // IMUEVENT_H
