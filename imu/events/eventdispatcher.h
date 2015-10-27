#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <iostream>
#include <vector>
#include "event.h"
#include "eventobserver.h"

using namespace std;

class EventDispatcher
{
public:
    EventDispatcher();
    ~EventDispatcher();

    void notify(Event* event);
    void registerObserver(EventObserver* eventObserver);
    void unregisterObserver(EventObserver* eventObserver);

private:
    bool isEventObserverPresent(EventObserver* eventObserver);
    vector<EventObserver*> eventObservers;
};

#endif // EVENTDISPATCHER_H
