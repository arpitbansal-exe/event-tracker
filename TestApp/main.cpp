#include <EventTracker.hpp>

int main() {
    EventTracker::init("https://api.yourdomain.com/events", "1.0.0");
    EventTracker::setGlobalFields({{"scn", "9483943"}});
    EventTracker::event("job_executed", {
        {"ret value", "9483943"},
        {"job_id", "JX-1299"}
    });

    return 0;
}