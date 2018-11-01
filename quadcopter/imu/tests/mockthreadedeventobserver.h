#ifndef TESTTHREADEDEVENTOBSERVER_H
#define TESTTHREADEDEVENTOBSERVER_H

#include <vector>
#include <string>
#include "../events/threadedeventobserver.h"

class MockThreadedEventObserver : public ThreadedEventObserver
{
public:
    MockThreadedEventObserver();
    MockThreadedEventObserver(string name, condition_variable& conditionVar);
    ~MockThreadedEventObserver();

    void processEvent(Event* event);
    void setProcessingDelay(int processingDelay) { this->processingDelay = processingDelay; }

    int getNumberOfEvents() { return nrOfEvents; }
    vector<int> getCounters() { return counters; }

private:
    int nrOfEvents;
    int processingDelay;
    vector<int> counters;
    string name;
    condition_variable* conditionVar;
};

#endif // TESTTHREADEDEVENTOBSERVER_H
