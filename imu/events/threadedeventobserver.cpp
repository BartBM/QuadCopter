#include "threadedeventobserver.h"
#include <iostream>

ThreadedEventObserver::ThreadedEventObserver()
{
    threadingEnabled = true;
    eventAdded = false;
    worker = new thread(&ThreadedEventObserver::consumeEvents, this);
}

ThreadedEventObserver::~ThreadedEventObserver()
{
    worker->join();
    delete worker;
}

void ThreadedEventObserver::onEvent(Event& event)
{
    events.push_back(event);
    cout << "events size: " << events.size() << endl;

    {
        std::lock_guard<std::mutex> lockGuard(mutexLock);
        eventAdded = true;
    }
    cout << "notify" << endl;
    conditionVar.notify_one();
}

void ThreadedEventObserver::consumeEvents()
{
    while (threadingEnabled) {

        // wait for notify
        cout << "waiting..." << endl;
        unique_lock<mutex> uniqueLock(mutexLock);
        cout << "uniqueLock..." << endl;
        conditionVar.wait(uniqueLock, [this]{ return eventAdded; });
        cout << "after waiting" << endl;
        cout << "d events size: " << events.size() << endl;
        eventAdded = false;
        cout << "g events size: " << events.size() << endl;

        while (events.size() > 0) {
            processEvent(events.front());
            events.pop_front();
        }
    }
}
