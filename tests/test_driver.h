#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../src/scheduler.h"
#include "../src/simulator.h"
#include "../src/thread.h"

struct TestResult {
    int total_time;
    int total_threads;
    int total_blocked_time;
    int total_wait_time;
    double average_wait_time;
    double average_turnaround_time;
};

class TestDriver {
private:
    // The simulator to run the test with
    std::unique_ptr<Simulator>  simulator;
    // Create threads from a JSON configuration
    std::vector<std::shared_ptr<Thread>> create_threads_from_json(const nlohmann::json& test_config);
    // Set up the simulation with the given threads
    void setup_simulation(const std::vector<std::shared_ptr<Thread>>& threads);
    // Collect metrics from the simulation 
    TestResult collect_metrics(const Simulator& simulator, const std::vector<std::shared_ptr<Thread>>& threads);

public:
    TestDriver(std::unique_ptr<Scheduler> scheduler);
    
    // Run a single test from a JSON file
    TestResult run_test(const std::string& test_file);
    
    // Run all tests in a directorys
    std::vector<TestResult> run_all_tests(const std::string& test_dir);
};

#endif 