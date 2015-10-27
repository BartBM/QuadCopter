#ifndef MOCKEVENT_H
#define MOCKEVENT_H

#include "../events/event.h"

class MockEvent : public Event
{
public:
    MockEvent(int value) { this->value = value; }
    MockEvent(const MockEvent& mockEvent) { this->value = mockEvent.value; }
    MockEvent& operator= (const MockEvent& m) {
        this->value = m.value;
        return *this;
    }
    ~MockEvent() {}

    EventType getEventType()
    {
        return EventType::MOCK;
    }

    Event* clone() {
        return new MockEvent(*this);
    }

    int getValue() { return value; }

private:
    int value;
};

#endif // MOCKEVENT_H
