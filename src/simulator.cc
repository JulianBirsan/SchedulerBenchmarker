#include "simulator.h"

Simulator::Simulator(std::unique_ptr<Scheduler> scheduler) : scheduler{std::move(scheduler)} {}

void Simulator::add_event(const Event& event) {
    event_queue.push(event);
}

void Simulator::simulate_events() {
    
}