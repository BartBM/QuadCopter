#ifndef EVENTOBSERVER_H
#define EVENTOBSERVER_H

#include "event.h"

class EventObserver
{
public:
    EventObserver();
    ~EventObserver();

    virtual void onEvent(Event* event) = 0;

};

#endif // EVENTOBSERVER_H
