#include <EventTracker.hpp>
#define SERVER_URL "https://bansal.free.beeceptor.com"
int main() {
    EventTracker::init(SERVER_URL, "1.0.0");
    EventTracker::setTestMode(false);
    EventTracker::setGlobalFields({{"scn", "9483943"}});
    EventTracker::enableDeviceInfo(DeviceInfoFlags::ALL_INFO);
    EventTracker::event("job_executed", {
        {"ret value", "9483943"},
        {"job_id", "JX-1299"}
    });

    EventTracker::flush();    
    EventTracker::shutdown();

    return 0;
}