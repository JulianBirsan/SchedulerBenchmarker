#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../src/scheduler.h"
#include "../src/simulator.h"
#include "../src/thread.h"

class TestDriver {
private:
    // The simulator to run the test with
    std::unique_ptr<Simulator>  simulator;
    // Create threads from a JSON configuration
    std::vector<std::shared_ptr<Thread>> create_threads_from_json(const nlohmann::json& test_config);
    // Set up the simulation with the given threads
    void setup_simulation(const std::vector<std::shared_ptr<Thread>>& threads);

public:
    TestDriver(std::unique_ptr<Scheduler> scheduler);
    
    // Run a single test from a JSON file
    Metrics run_test(const std::string& test_file);
    
    // Run all tests in a directorys
    std::vector<Metrics> run_all_tests(const std::string& test_dir);
};

#endif 