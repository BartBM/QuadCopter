#include "catch.h"
#include "mockthreadedeventobserver.h"

TEST_CASE( "FIFO update mechanism", "[ThreadedEventObserver]") {
    MockThreadedEventObserver* mockThreadedEventObserver = new MockThreadedEventObserver();
    Event event;

    mockThreadedEventObserver->onEvent(event);
    REQUIRE(mockThreadedEventObserver->getCounters().size() == 1);

    mockThreadedEventObserver->onEvent(event);
    REQUIRE(mockThreadedEventObserver->getCounters().size() == 2);
}
