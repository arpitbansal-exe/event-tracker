#include <EventTrackerPublic.hpp>
#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

#define SERVER_URL "http://127.0.0.1:8000/test"
#define AUTH_TOKEN "super-secret-token"

class EventGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> user_dist;
    std::uniform_int_distribution<> job_dist;
    std::uniform_int_distribution<> error_dist;
    std::uniform_real_distribution<> success_rate;
    std::uniform_int_distribution<> delay_dist;

    std::vector<std::string> user_ids = { "U-1001", "U-1002", "U-1003", "U-1004", "U-1005", "U-1006", "U-1007", "U-1008", "U-1009", "U-1010" };
    std::vector<std::string> job_types = { "data_processing", "ml_training", "backup", "report_generation", "data_sync", "cleanup", "monitoring" };
    std::vector<std::string> error_codes = { "ERR_TIMEOUT", "ERR_MEMORY", "ERR_NETWORK", "ERR_PERMISSION", "ERR_DISK_FULL", "ERR_CONNECTION" };
    std::vector<std::string> file_types = { "csv", "json", "xml", "pdf", "xlsx", "txt", "log" };
    std::vector<std::string> alert_levels = { "info", "warning", "error", "critical" };
    std::vector<std::string> regions = { "us-east-1", "us-west-2", "eu-west-1", "ap-south-1", "ca-central-1" };
    std::vector<std::string> environments = { "prod", "staging", "dev", "test" };

public:
    EventGenerator() : gen(rd()), user_dist(0, 9), job_dist(1000, 9999), error_dist(0, 5),
        success_rate(0.0, 1.0), delay_dist(100, 2000) {
    }

    std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::stringstream ss;
        ss << std::put_time(std::gmtime(&time_t), "%Y-%m-%dT%H:%M:%S");
        ss << "." << std::setfill('0') << std::setw(3) << ms.count() << "Z";
        return ss.str();
    }

    void generateUserActivity() {
        std::string user_id = user_ids[user_dist(gen)];

        // User login
        EventTracker::event("user_login", {
            {"user_id", user_id},
            {"login_time", getCurrentTimestamp()},
            {"ip_address", "192.168.1." + std::to_string(user_dist(gen) + 10)},
            {"browser", "Chrome"},
            {"session_id", "sess_" + std::to_string(job_dist(gen))}
            });

        std::this_thread::sleep_for(std::chrono::milliseconds(delay_dist(gen)));

        // User action
        if (success_rate(gen) > 0.2) {
            EventTracker::event("user_action", {
                {"user_id", user_id},
                {"action", "dashboard_view"},
                {"timestamp", getCurrentTimestamp()},
                {"page", "/dashboard"},
                {"duration_ms", std::to_string(delay_dist(gen))}
                });
        }
    }

    void generateJobEvents() {
        std::string job_id = "JX-" + std::to_string(job_dist(gen));
        std::string job_type = job_types[job_dist(gen) % job_types.size()];

        // Job started
        EventTracker::event("job_started", {
            {"job_id", job_id},
            {"job_type", job_type},
            {"start_time", getCurrentTimestamp()},
            {"initiated_by", user_ids[user_dist(gen)]},
            {"priority", std::to_string(user_dist(gen) % 5 + 1)},
            {"environment", environments[user_dist(gen) % environments.size()]}
            });

        std::this_thread::sleep_for(std::chrono::milliseconds(delay_dist(gen)));

        // Job progress (maybe)
        if (success_rate(gen) > 0.5) {
            EventTracker::event("job_progress", {
                {"job_id", job_id},
                {"progress_percent", std::to_string(user_dist(gen) * 10)},
                {"timestamp", getCurrentTimestamp()},
                {"processed_items", std::to_string(job_dist(gen))},
                {"eta_seconds", std::to_string(delay_dist(gen))}
                });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay_dist(gen)));

        // Job completion or failure
        if (success_rate(gen) > 0.25) { // 75% success rate
            EventTracker::event("job_completed", {
                {"job_id", job_id},
                {"job_type", job_type},
                {"completion_time", getCurrentTimestamp()},
                {"duration_seconds", std::to_string(delay_dist(gen))},
                {"items_processed", std::to_string(job_dist(gen))},
                {"output_size_mb", std::to_string(success_rate(gen) * 100)}
                });
        }
        else {
            EventTracker::event("job_failed", {
                {"job_id", job_id},
                {"job_type", job_type},
                {"error_time", getCurrentTimestamp()},
                {"error_code", error_codes[error_dist(gen)]},
                {"retries", std::to_string(user_dist(gen) % 4)},
                {"duration_seconds", std::to_string(delay_dist(gen))},
                {"partial_results", success_rate(gen) > 0.5 ? "true" : "false"}
                });
        }
    }

    void generateSystemEvents() {
        // System alerts with varying severity
        std::string level = alert_levels[user_dist(gen) % alert_levels.size()];
        std::vector<std::string> messages = {
            "CPU usage at " + std::to_string(70 + user_dist(gen)) + "%",
            "Memory usage at " + std::to_string(60 + user_dist(gen) * 3) + "%",
            "Disk space low on /var/log",
            "Network latency spike detected",
            "Database connection pool exhausted",
            "Cache hit ratio below threshold"
        };

        EventTracker::event("system_alert", {
            {"level", level},
            {"message", messages[user_dist(gen) % messages.size()]},
            {"timestamp", getCurrentTimestamp()},
            {"source", "monitoring_system"},
            {"region", regions[user_dist(gen) % regions.size()]},
            {"node_id", "node-" + std::to_string(user_dist(gen) + 1)}
            });

        // Resource allocation
        EventTracker::event("resource_allocated", {
            {"resource_id", "VM-" + std::to_string(100 + user_dist(gen))},
            {"allocated_to", "JX-" + std::to_string(job_dist(gen))},
            {"cpu_cores", std::to_string(2 + user_dist(gen) % 8)},
            {"ram_gb", std::to_string(4 + user_dist(gen) % 16)},
            {"storage_gb", std::to_string(50 + user_dist(gen) * 10)},
            {"region", regions[user_dist(gen) % regions.size()]},
            {"timestamp", getCurrentTimestamp()}
            });
    }

    void generateDataEvents() {
        std::string user_id = user_ids[user_dist(gen)];
        std::string file_type = file_types[user_dist(gen) % file_types.size()];

        // Data upload
        EventTracker::event("data_uploaded", {
            {"user_id", user_id},
            {"file_size_mb", std::to_string(success_rate(gen) * 50)},
            {"file_type", file_type},
            {"upload_time", getCurrentTimestamp()},
            {"upload_duration_ms", std::to_string(delay_dist(gen))},
            {"compression_ratio", std::to_string(success_rate(gen))},
            {"region", regions[user_dist(gen) % regions.size()]}
            });

        // Data processing
        if (success_rate(gen) > 0.3) {
            EventTracker::event("data_processed", {
                {"user_id", user_id},
                {"records_processed", std::to_string(job_dist(gen) * 10)},
                {"processing_time_ms", std::to_string(delay_dist(gen) * 2)},
                {"timestamp", getCurrentTimestamp()},
                {"data_quality_score", std::to_string(success_rate(gen))},
                {"errors_found", std::to_string(user_dist(gen) % 5)}
                });
        }
    }

    void generateAPIEvents() {
        std::vector<std::string> endpoints = { "/api/users", "/api/jobs", "/api/data", "/api/reports", "/api/health" };
        std::vector<std::string> methods = { "GET", "POST", "PUT", "DELETE" };
        std::vector<int> status_codes = { 200, 201, 400, 401, 403, 404, 500, 502, 503 };

        EventTracker::event("api_request", {
            {"endpoint", endpoints[user_dist(gen) % endpoints.size()]},
            {"method", methods[user_dist(gen) % methods.size()]},
            {"status_code", std::to_string(status_codes[user_dist(gen) % status_codes.size()])},
            {"response_time_ms", std::to_string(10 + delay_dist(gen) / 10)},
            {"user_id", user_ids[user_dist(gen)]},
            {"timestamp", getCurrentTimestamp()},
            {"user_agent", "EventTracker/1.1.0"},
            {"request_size_bytes", std::to_string(100 + user_dist(gen) * 50)}
            });
    }

    void generateBusinessEvents() {
        // Purchase events
        EventTracker::event("purchase_completed", {
            {"transaction_id", "TXN-" + std::to_string(job_dist(gen))},
            {"user_id", user_ids[user_dist(gen)]},
            {"amount", std::to_string(success_rate(gen) * 1000)},
            {"currency", "USD"},
            {"payment_method", "credit_card"},
            {"timestamp", getCurrentTimestamp()},
            {"items_count", std::to_string(user_dist(gen) % 10 + 1)}
            });

        // Feature usage
        std::vector<std::string> features = { "dashboard", "reports", "analytics", "export", "sharing" };
        EventTracker::event("feature_used", {
            {"user_id", user_ids[user_dist(gen)]},
            {"feature", features[user_dist(gen) % features.size()]},
            {"usage_duration_seconds", std::to_string(delay_dist(gen) / 100)},
            {"timestamp", getCurrentTimestamp()},
            {"session_id", "sess_" + std::to_string(job_dist(gen))}
            });
    }
};

int main() {
    // Initialize EventTracker
    QueueConfig queue_config;
    queue_config.maxQueueSize = 100;
    queue_config.batchSize = 20;
    queue_config.maxRetries = 3;
    queue_config.retryDelayMs = 500;
    queue_config.dropPolicy = DropPolicy::DROP_OLDEST;
    queue_config.authToken = AUTH_TOKEN;

    EventTracker::init(SERVER_URL, "1.1.1", queue_config);
    EventTracker::setTestMode(false);
    EventTracker::setGlobalFields({
        {"environment", "load_test"},
        {"test_run_id", std::to_string(std::time(nullptr))}
        });
    EventTracker::enableDeviceInfo(DeviceInfoFlags::ALL_INFO);

    EventGenerator generator;

    std::cout << "Starting load test with variety of events..." << std::endl;
    std::cout << "Press Ctrl+C to stop" << std::endl;

    // Generate events for specified duration or indefinitely
    int total_events = 0;
    auto start_time = std::chrono::steady_clock::now();

    // Run for 5 minutes or until interrupted
    while (std::chrono::steady_clock::now() - start_time < std::chrono::minutes(5)) {
        // Generate different types of events in cycles
        generator.generateUserActivity();
        total_events++;

        generator.generateJobEvents();
        total_events++;

        generator.generateSystemEvents();
        total_events++;

        generator.generateDataEvents();
        total_events++;

        generator.generateAPIEvents();
        total_events++;

        generator.generateBusinessEvents();
        total_events++;

        // Print progress
        if (total_events % 50 == 0) {
            std::cout << "Generated " << total_events << " events..." << std::endl;
        }

        // Small delay between batches
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Flushing remaining events..." << std::endl;
    EventTracker::flush();

    std::cout << "Shutting down..." << std::endl;
    EventTracker::shutdown();

    std::cout << "Load test completed. Generated " << total_events << " events." << std::endl;
    return 0;
}