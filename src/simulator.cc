#include "simulator.h"

Simulator::Simulator(std::unique_ptr<Scheduler> scheduler) : scheduler{std::move(scheduler)}, current_time{0} {}

void Simulator::add_event(const Event& event) {
    event_queue.push(event);
}

void Simulator::simulate_events() {
    // we are done if there are no more arriving threads and no running thread
    while (!event_queue.empty() || current_thread.get() != nullptr) {
        // go to next time slice
        current_time++;

        // process events that occur at this time
        while (!event_queue.empty() && event_queue.top().time == current_time) {
            Event event = event_queue.top();
            event_queue.pop();
            current_time = event.time;

            if (event.type == EventType::THREAD_ARRIVAL) {
                // TODO: make sure it is ready first
                scheduler.get()->handle_new_thread(event.thread);
            }
        }

        // first, let current thread run (or block itself) for a time slice

        if (current_thread.get() == nullptr) {
            // no current running thread, let scheduler select a new one
            current_thread = scheduler.get()->select_thread();
        } else {
            // running thread must be in running state
            assert (current_thread.get()->get_state() != ThreadState::RUNNING);
    
            current_thread.get()->run();

            if (current_thread.get()->get_state() == ThreadState::BLOCKED) {
                 // the thread just blocked, add an event to unblock
                event_queue.push({
                    current_time + current_thread.get()->get_block_time(),
                    EventType::THREAD_ARRIVAL,
                    current_thread
                });
                // the thread will be replaced in the NEXT time slice
                current_thread = nullptr;
            } else if (current_thread.get()->get_state() == ThreadState::TERMINATED) {
                // TODO: log information
                current_thread = nullptr;
            }
        }
        
        // let the scheduler handle the time slice
        scheduler.get()->handle_tick(current_thread);
    }
}