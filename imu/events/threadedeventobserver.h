#ifndef THREADEDEVENTOBSERVER_H
#define THREADEDEVENTOBSERVER_H

#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "events/event.h"
#include "eventobserver.h"

using namespace std;

class ThreadedEventObserver : public EventObserver
{
public:
    ThreadedEventObserver();
    ~ThreadedEventObserver();

    void onEvent(Event& event);
    void consumeEvents();
    virtual void processEvent(Event& event) = 0;
    thread* getThread() { return worker; }

private:
    bool threadingEnabled, eventAdded;
    mutex mutexLock;
    deque<Event> events;
    condition_variable conditionVar;
    thread* worker;

};

#endif // THREADEDEVENTOBSERVER_H
