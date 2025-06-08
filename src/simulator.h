#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <memory>
#include <vector>
#include <queue>

#include "scheduler.h"

// TODO: are there any events outside of thread arrivals?
enum class EventType { THREAD_ARRIVAL, TICK };

struct Event {
    int time;
    EventType type;
    std::shared_ptr<Thread> thread;

    bool operator<(const Event &o) const {
        return time < o.time;
    }
};

class Simulator {
private:
    // the scheduler to use for this simulator
    std::unique_ptr<Scheduler> scheduler;
    // queue of events to process, defined by the test
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> event_queue;
    // current running thread
    std::shared_ptr<Thread> current_thread;
    // the current time slice
    int current_time;

public:
    Simulator(std::unique_ptr<Scheduler> scheduler);
    // add an event to the queue
    void add_event(const Event& event);
    // main simulation logic
    void simulate_events();
};

#endif