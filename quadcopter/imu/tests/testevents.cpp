#include <unistd.h>
#include <iostream>
#include <condition_variable>
#include <mutex>
#include "catch.h"
#include "mockthreadedeventobserver.h"
#include "../events/imuevent.h"
#include "../tests/mockevent.h"

using namespace std;

TEST_CASE( "FIFO update mechanism", "[ThreadedEventObserver]") {
    condition_variable cvar;

    MockThreadedEventObserver* observer = new MockThreadedEventObserver("thread1", cvar);
    Event* event = new MockEvent(5);

    for (int i=0; i<100; ++i) {
        observer->onEvent(event);
    }

    mutex mutex1;
    unique_lock<mutex> uniqueLock1(mutex1);
    cvar.wait(uniqueLock1, [observer]{ return observer->getNumberOfEvents() == 100; });
}


TEST_CASE( "FIFO update mechanism with processing delay", "[ThreadedEventObserver]") {
    condition_variable cvar;

    MockThreadedEventObserver* observer1 = new MockThreadedEventObserver("thread1", cvar);
    //observer1->setProcessingDelay(50);

    MockThreadedEventObserver* observer2 = new MockThreadedEventObserver("thread2", cvar);
    //observer2->setProcessingDelay(55);

    Event* event = new MockEvent(5);

    for (int i=0; i<100; ++i) {
        observer1->onEvent(event);
        observer2->onEvent(event);
    }

    mutex mutex1;
    unique_lock<mutex> uniqueLock1(mutex1);
    cvar.wait(uniqueLock1, [observer1, observer2]{ return (observer1->getNumberOfEvents() + observer2->getNumberOfEvents()) == 200; });
}

