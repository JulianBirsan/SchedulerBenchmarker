#include "simulator.h"

Simulator::Simulator(std::unique_ptr<Scheduler> scheduler) : scheduler{std::move(scheduler)}, current_time{0} {}

void Simulator::add_event(const Event& event) {
    event_queue.push(event);
}

void Simulator::simulate_events() {
    // TODO: keep track of time for scheduler to make each decision
    // we are done if there are no more arriving threads and no running thread
    while (!event_queue.empty() || current_thread != nullptr) {
        // go to next time slice
        current_time++;

        // process events that occur at this time
        while (!event_queue.empty() && event_queue.top().time == current_time) {
            Event event = event_queue.top();
            event_queue.pop();

            if (event.type == EventType::THREAD_ARRIVAL) {
                event.thread->make_ready();
                scheduler->handle_new_thread(event.thread);
            }
        }

        // first, let current thread run (or block itself) for a time slice

        if (current_thread == nullptr) {
            // no current running thread, let scheduler select a new one
            current_thread = scheduler->select_thread();
        } else {
            // running thread must be in running state
            assert (current_thread->get_state() != ThreadState::RUNNING);
    
            current_thread->run();

            if (current_thread->get_state() == ThreadState::BLOCKED) {
                 // the thread just blocked, add an event to unblock
                event_queue.push({
                    current_time + current_thread->get_block_time(),
                    EventType::THREAD_ARRIVAL,
                    current_thread
                });
                // the thread will be replaced in the NEXT time slice
                current_thread = nullptr;
            } else if (current_thread->get_state() == ThreadState::READY) {
                // the thread just got preempted
                scheduler->handle_new_thread(current_thread);
                current_thread = nullptr;
            } else if (current_thread->get_state() == ThreadState::TERMINATED) {
                // TODO: log information
                handle_thread_done(current_thread->get_arrival_time(), current_time);
                current_thread = nullptr;
            }
            // let the scheduler handle the time slice
            scheduler->handle_tick(current_thread);
        }
    }
}

void Simulator::handle_thread_done(int arrival_time, int end_time) {
    turn_around_time += end_time - arrival_time;
}

Metrics Simulator::get_metrics() {
    return {turn_around_time};
}