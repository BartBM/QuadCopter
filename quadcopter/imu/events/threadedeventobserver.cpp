#include "threadedeventobserver.h"
#include <iostream>

ThreadedEventObserver::ThreadedEventObserver()
{
    threadingEnabled = true;
    worker = new thread(&ThreadedEventObserver::consumeEvents, this);
}

ThreadedEventObserver::~ThreadedEventObserver()
{
    cout << "ThreadedEventObserver destructor...";
    stopWorker();
    conditionVar.notify_one();
    worker->join();
    delete worker;
    cout << "done" << endl;
}

void ThreadedEventObserver::onEvent(Event* event)
{
    events.push_back(event->clone());
    conditionVar.notify_one();
}

void ThreadedEventObserver::consumeEvents()
{
    while (threadingEnabled) {

        // wait for notify
        unique_lock<mutex> uniqueLock(mutexLock);
        conditionVar.wait(uniqueLock, [this]{ return !events.empty() || !threadingEnabled; });

        while (events.size() > 0) {
            processEvent(events.front());
            events.pop_front();
        }
    }
}
