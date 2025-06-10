#include <EventTrackerPublic.hpp>
#define SERVER_URL "http://127.0.0.1:8000/test"
#define AUTH_TOKEN "super-secret-token"
int main() {

    QueueConfig queue_config;
    queue_config.maxQueueSize = 50;                       // Hold up to 50 events
    queue_config.batchSize = 10;                           // Send 5 at a time
    queue_config.maxRetries = 2;                          // Retry each batch up to 2 times
    queue_config.retryDelayMs = 1000;                     // Wait 1s between retries
    queue_config.dropPolicy = DropPolicy::DROP_OLDEST;    // Drop oldest when full
	queue_config.authToken = AUTH_TOKEN;                  // Set auth token for server


    EventTracker::init(SERVER_URL, "1.1.0", queue_config);
    EventTracker::setTestMode(false);
    EventTracker::setGlobalFields({{"scn", "9483943"}});
    EventTracker::enableDeviceInfo(DeviceInfoFlags::ALL_INFO);
    EventTracker::event("job_executed", {
        {"ret value", "9483943"},
        {"job_id", "JX-1299"}
    });
    EventTracker::event("job_started", {
    {"start_time", "2025-06-09T08:30:00Z"},
    {"job_id", "JX-1300"},
    {"initiated_by", "admin"}
        });

    EventTracker::event("job_failed", {
        {"error_code", "ERR_TIMEOUT"},
        {"job_id", "JX-1301"},
        {"retries", "3"},
        {"duration", "120s"}
        });

    EventTracker::event("data_uploaded", {
        {"user_id", "U-9843"},
        {"file_size", "2.4MB"},
        {"upload_time", "2025-06-09T09:00:00Z"},
        {"file_type", "csv"}
        });

    EventTracker::event("system_alert", {
        {"level", "critical"},
        {"message", "Memory usage exceeded 90%"},
        {"timestamp", "2025-06-09T09:15:00Z"}
        });

    EventTracker::event("user_login", {
        {"user_id", "U-1001"},
        {"login_time", "2025-06-09T07:45:00Z"},
        {"ip_address", "192.168.1.12"}
        });

    EventTracker::event("resource_allocated", {
        {"resource_id", "VM-203"},
        {"allocated_to", "JX-1299"},
        {"cpu_cores", "4"},
        {"ram", "8GB"},
        {"duration", "2h"}
        });
    //EventTracker::event("job_1", {});
    //EventTracker::event("job_2", {});
    //EventTracker::event("job_3", {});
    //EventTracker::event("job_4", {});
    //EventTracker::event("job_5", {});

 
    //EventTracker::event("job_6", {});
    //EventTracker::event("job_7", {});
    //EventTracker::event("job_8", {});
    //EventTracker::event("job_9", {});

    EventTracker::flush();
    EventTracker::shutdown();

    return 0;
}