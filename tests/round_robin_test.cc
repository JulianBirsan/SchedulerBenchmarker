#include <iostream>

#include "test_driver.h"
#include "../examples/schedulers/round_robin.h"

int main() {
    // Round Robin with quantum 4
    TestDriver driver(std::make_unique<RoundRobin>(4));
    std::vector<Metrics> metrics = driver.run_all_tests("tests/threads");
    for (auto& metric: metrics) {
        std::cout << metric.turn_around_time << "\n";
    }
    return 0;
} 