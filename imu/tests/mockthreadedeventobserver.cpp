#include <iostream>
#include "mockthreadedeventobserver.h"
#include "mockevent.h"

MockThreadedEventObserver::MockThreadedEventObserver()
{

}

MockThreadedEventObserver::~MockThreadedEventObserver()
{

}

void MockThreadedEventObserver::processEvent(Event event)
{

    cout << "start counter: " << counter << endl;

    if (MockEvent* mockedEvent = dynamic_cast<MockEvent*>(&event)) {
        counters.push_back(mockedEvent->getValue());
    }

    cout << "end counter: " << counter << endl;
}
