#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include "threadedeventobserver.h"

class EventLogger : public ThreadedEventObserver
{
public:
    EventLogger();
    ~EventLogger();

    void processEvent(Event* event);
};

#endif // EVENTLOGGER_H
