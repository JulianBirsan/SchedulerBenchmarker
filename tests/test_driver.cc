#include "test_driver.h"
#include <fstream>
#include <filesystem>
#include <iostream>

TestDriver::TestDriver(std::unique_ptr<Scheduler> scheduler) 
    : scheduler(std::move(scheduler)) {}

std::vector<std::shared_ptr<Thread>> TestDriver::create_threads_from_json(const nlohmann::json& test_config) {
    std::vector<std::shared_ptr<Thread>> threads;
    
    for (const auto& thread_config : test_config["threads"]) {
        threads.push_back(std::make_shared<Thread>(
            thread_config["id"].get<int>(),
            thread_config["remaining_run_time"].get<int>(),
            thread_config["block_chance"].get<double>(),
            thread_config["avg_block_duration"].get<int>(),
            thread_config["sd_block_duration"].get<int>(),
            thread_config["arrival_time"].get<int>()
        ));
    }
    
    return threads;
}

void TestDriver::setup_simulation(const std::vector<std::shared_ptr<Thread>>& threads) {
    for (const auto& thread : threads) {
        simulator.add_event({
            thread->get_arrival_time(), 
            EventType::THREAD_ARRIVAL,
            thread
        });
    }
}

TestResult TestDriver::collect_metrics(const Simulator& simulator, const std::vector<std::shared_ptr<Thread>>& threads) {
    TestResult result;
    
    // TODO: Implement actual metric collection
    // This would require adding methods to Simulator and Thread to track:
    // - Blocked time
    // - Wait time
    // - Turnaround time
    
    return result;
}

TestResult TestDriver::run_test(const std::string& test_file) {
    // Load test configuration
    std::ifstream file(test_file);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open test file: " + test_file);
    }
    
    nlohmann::json test_config;
    file >> test_config;
    
    // Create threads from configuration
    std::vector<std::shared_ptr<Thread>> threads = create_threads_from_json(test_config);
    
    // Setup simulation
    setup_simulation(simulator, threads);
    
    // Run simulation
    simulator.simulate_events();
    
    // Collect and return metrics
    return collect_metrics(simulator, threads);
}

std::vector<TestResult> TestDriver::run_all_tests(const std::string& test_dir) {
    std::vector<TestResult> results;
    
    for (const auto& entry : std::filesystem::directory_iterator(test_dir)) {
        if (entry.path().extension() == ".json") {
            try {
                results.push_back(run_test(entry.path().string()));
            } catch (const std::exception& e) {
                std::cerr << "Error running test " << entry.path() << ": " << e.what() << std::endl;
            }
        }
    }
    
    return results;
} 