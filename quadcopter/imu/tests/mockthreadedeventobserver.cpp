#include <iostream>
#include "mockthreadedeventobserver.h"
#include "mockevent.h"
#include <unistd.h>
#include <condition_variable>

MockThreadedEventObserver::MockThreadedEventObserver() {
    nrOfEvents = 0;
    processingDelay = 0;
}

MockThreadedEventObserver::MockThreadedEventObserver(string name, condition_variable& conditionVar)
{
    this->name = name;
    this->conditionVar = &conditionVar;
    nrOfEvents = 0;
    processingDelay = 0;
}

MockThreadedEventObserver::~MockThreadedEventObserver()
{

}

void MockThreadedEventObserver::processEvent(Event* event)
{
    usleep(processingDelay);
    if (MockEvent* mockedEvent = dynamic_cast<MockEvent*>(event)) {
        ++nrOfEvents;
        counters.push_back(mockedEvent->getValue());
    }
    conditionVar->notify_one();

}
