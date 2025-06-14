#include <iostream>
#include <memory>
#include "scheduler.h"
#include "schedulers/round_robin.h"
#include "simulator.h"

int main() {
    // Create a round robin scheduler with quantum 10
    auto scheduler = std::make_unique<RoundRobin>(10);
    
    // Create simulator with the scheduler
    Simulator simulator(std::move(scheduler));
    
    // TODO: Add test threads and run simulation
    
    std::cout << "Scheduler Benchmarker" << std::endl;
    return 0;
} 