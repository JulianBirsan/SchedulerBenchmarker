#include "test_driver.h"
#include "../src/schedulers/round_robin.h"

int main() {
    // Round Robin with quantum 4
    Simulator simulator(std::make_unique<RoundRobin>(4));
    TestDriver driver(std::make_unique<Simulator>(simulator));
    driver.run_all_tests("tests/threads");
    return 0;
}