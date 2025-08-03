#include <iostream>
#include <memory>
#include <vector>

#include "test_driver.h"
#include "../src/simulator.h"
#include "../src/schedulers/round_robin.h"
#include "../src/schedulers/mlfq.h"

void test_scheduler(TestDriver driver, std::string scheduler_name) {
    std::vector<Metrics> metrics = driver.run_all_tests("tests/threads");
    std::cout << "\n----------------------------\n";
    std::cout << "Testing " << scheduler_name << "\n";
    for (auto& metric: metrics) {
        std::cout << "turn around time: ";
        std::cout << metric.turn_around_time << "\n";
    }
    std::cout << "\n----------------------------\n";
}

int main() {
    // round robin with quantum 4
    test_scheduler(TestDriver(std::make_unique<RoundRobin>(4)), "Round Robin");
    // mlfq with 3 levels with quantums 2, 4, 8
    std::vector<int> quantums = {2, 4, 8};
    test_scheduler(TestDriver(std::make_unique<MLFQ>(quantums)), "MLFQ");
    return 0;
}