# SchedulerBenchmarker

A C++ framework for testing and benchmarking thread schedulers. This project provides a simple API to implement and compare different scheduling algorithms through simulation.

## Overview

SchedulerBenchmarker allows you to:
- Implement custom thread schedulers by extending the `Scheduler` base class
- Test schedulers with configurable thread workloads defined in JSON
- Compare scheduler performance using metrics like turn-around time
- Simulate realistic thread behavior including blocking and preemption

## Project Structure

```
SchedulerBenchmarker/
├── src/                    # Core framework
│   ├── scheduler.h         # Abstract Scheduler base class
│   ├── thread.h/cc         # Thread implementation
│   └── simulator.h/cc      # Simulation engine
├── examples/               # Example scheduler implementations
│   └── schedulers/
│       ├── round_robin.h/cc    # Round Robin scheduler
│       └── mlfq.h/cc           # Multi-Level Feedback Queue
├── tests/                  # Test files and configurations
│   ├── main.cc             # Main test runner
│   ├── test_driver.h/cc    # Test driver implementation
│   └── threads/            # Thread workload definitions
│       └── test1.json      # Sample thread configuration
├── Makefile                # Build configuration
└── README.md              # This file
```

## Building

### Prerequisites
- C++17 compatible compiler (GCC, Clang, or MSVC)
- nlohmann/json library (header-only, included in `/usr/local/include`)

### Build Commands

```bash
# Build the main test executable
make tests_main

# Build all (same as tests_main)
make all

# Clean build artifacts
make clean

# Build and run in one command
make tests_main && ./tests_main
```

## Usage

### Running Tests

The main test runner compares schedulers defined in `examples/`:

```bash
./tests_main
```

## Implementing Custom Schedulers

### 1. Extend the Scheduler Base Class

Create a new scheduler by inheriting from `Scheduler`:

```cpp
#include "../../src/scheduler.h"
#include "../../src/thread.h"
#include <queue>

class MyScheduler : public Scheduler {
private:
    // Your scheduler's internal state
    // e.g., quantum, ready queue, etc.

public:
    MyScheduler(int quantum) : quantum(quantum) {}

    // Called when a new thread becomes ready
    void handle_new_thread(std::shared_ptr<Thread> thread) override {
        // Implement your logic here
        // e.g., add to ready queue
    }

    // Called to select the next thread to run
    std::shared_ptr<Thread> select_thread() override {
        // Implement your logic here, returning nullptr if there is no thread to select
    }

    // Called each tick while a thread is running
    void handle_tick(std::shared_ptr<Thread> current_thread) override {
        // Implement your scheduling logic here
        // e.g., quantum management, preemption, etc.
    }
};
```

### 2. Add to Build System

Update the Makefile to include your new scheduler:

```makefile
# Add your scheduler files
TESTS_MAIN_SRCS = tests/main.cc tests/test_driver.cc src/thread.cc src/simulator.cc examples/schedulers/round_robin.cc examples/schedulers/mlfq.cc examples/schedulers/my_scheduler.cc
```

### 3. Include in Tests

Add your scheduler to the test runner:

```cpp
#include "../examples/schedulers/my_scheduler.h"

int main() {
    test_scheduler(TestDriver(std::make_unique<MyScheduler>(...)), "My Scheduler");
    return 0;
}
```

## Thread Configuration

Threads are defined in JSON files under `tests/threads/`. Each thread has the following properties:

```json
{
    "id": 1,               
    "remaining_run_time": 100,   
    "block_chance": 0.1,     
    "avg_block_duration": 5,    
    "sd_block_duration": 2,     
    "arrival_time": 0          
}
```

### Thread Properties

id: Unique thread identifier
remaining_run_time: Total CPU time slices needed to run the thread
block_chance: Probability (0.0 - 1.0) of blocking per tick
avg_block_duration: Average time slices the thread will block for
sd_block_duration: Standard deviation of the block duration
arrival_time: When the thread arrives

## API Reference

### Scheduler Interface

```cpp
class Scheduler {
public:
    virtual ~Scheduler() = default;

    // Called when a new thread becomes ready
    virtual void handle_new_thread(std::shared_ptr<Thread> thread) = 0;
    
    // Called to select the next thread to run (return nullptr if none ready)
    virtual std::shared_ptr<Thread> select_thread() = 0;

    // Called each tick while a thread is running
    virtual void handle_tick(std::shared_ptr<Thread> current_thread) = 0;
};
```

### Metrics

The simulator collects the following metrics:

```cpp
struct Metrics {
    int turn_around_time;  // Total time from arrival to completion
};
```

This will be extended to collect other metrics, such as decision time

## Example Schedulers

### Round Robin
- **File**: `examples/schedulers/round_robin.h/cc`
- **Description**: Classic round-robin scheduling with fixed quantum
- **Usage**: `RoundRobin(quantum)`

### Multi-Level Feedback Queue (MLFQ)
- **File**: `examples/schedulers/mlfq.h/cc`
- **Description**: Multi-level queue with different quantums per level
- **Usage**: `MLFQ({quantum1, quantum2, quantum3})`
