#ifndef TESTTHREADEDEVENTOBSERVER_H
#define TESTTHREADEDEVENTOBSERVER_H

#include <vector>
#include "../events/threadedeventobserver.h"

using namespace std;

class MockThreadedEventObserver : public ThreadedEventObserver
{
public:
    MockThreadedEventObserver();
    ~MockThreadedEventObserver();

    void processEvent(Event event);

    vector<int> getCounters() { return counters; }

private:
    int counter;
    vector<int> counters;
};

#endif // TESTTHREADEDEVENTOBSERVER_H
