#ifndef EVENT_H
#define EVENT_H

enum class EventType {
    UNKNOWN,
    IMU,
    MOCK
};

class Event
{
public:
    virtual EventType getEventType() = 0;
    virtual Event* clone() = 0;
};

#endif // EVENT_H
