#include "eventdispatcher.h"
#include "threadedeventobserver.h"
#include <algorithm>

EventDispatcher::EventDispatcher()
{

}

EventDispatcher::~EventDispatcher()
{
    cout << "EventDispatcher destructor" << endl;
}

void EventDispatcher::notify(Event* event)
{
    for_each(eventObservers.begin(), eventObservers.end(), [&event](EventObserver* eventObserver) { eventObserver->onEvent(event); });
}

void EventDispatcher::registerObserver(EventObserver* eventObserver)
{
    if (!isEventObserverPresent(eventObserver)) {
        eventObservers.push_back(eventObserver);
    }
}

void EventDispatcher::unregisterObserver(EventObserver* eventObserver)
{
    eventObservers.erase(remove_if(eventObservers.begin(), eventObservers.end(), [eventObserver](EventObserver* element)->bool { return element == eventObserver; }));
}

bool EventDispatcher::isEventObserverPresent(EventObserver* eventObserver)
{
    for (EventObserver* m_eventObserver : eventObservers) {
        if (m_eventObserver == eventObserver) {
            return true;
        }
    }
    return false;
}
