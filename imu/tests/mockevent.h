#ifndef MOCKEVENT_H
#define MOCKEVENT_H

#include "../events/event.h"

class MockEvent : public Event
{
public:
    MockEvent(int value) { this->value = value; }
    ~MockEvent() {}

    EventType getEventType()
    {
        return EventType::MOCK;
    }
    int getValue() { return value; }

private:
    int value;
};

#endif // MOCKEVENT_H
