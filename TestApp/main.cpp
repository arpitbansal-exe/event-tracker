#include <EventTrackerPublic.hpp>
#define SERVER_URL "https://bansal.free.beeceptor.com"
int main() {

    QueueConfig queue_config;
    queue_config.maxQueueSize = 50;                       // Hold up to 50 events
    queue_config.batchSize = 10;                           // Send 5 at a time
    queue_config.maxRetries = 2;                          // Retry each batch up to 2 times
    queue_config.retryDelayMs = 1000;                     // Wait 1s between retries
    queue_config.dropPolicy = DropPolicy::DROP_OLDEST;    // Drop oldest when full


    EventTracker::init(SERVER_URL, "1.0.0", queue_config);
    EventTracker::setTestMode(false);
    EventTracker::setGlobalFields({{"scn", "9483943"}});
    EventTracker::enableDeviceInfo(DeviceInfoFlags::ALL_INFO);
    EventTracker::event("job_executed", {
        {"ret value", "9483943"},
        {"job_id", "JX-1299"}
    });
    EventTracker::event("job_1", {});
    EventTracker::event("job_2", {});
    EventTracker::event("job_3", {});
    EventTracker::event("job_4", {});
    EventTracker::event("job_5", {});


    EventTracker::flush();  
    EventTracker::event("job_6", {});
    EventTracker::event("job_7", {});
    EventTracker::event("job_8", {});
    EventTracker::event("job_9", {});
    EventTracker::shutdown();

    return 0;
}