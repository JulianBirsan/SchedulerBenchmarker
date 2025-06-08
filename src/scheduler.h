#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <memory>

#include "thread.h"

class Scheduler {
public:
    virtual ~Scheduler();

    // Called when a new thread is ready
    virtual void handle_new_thread(std::unique_ptr<Thread> thread) = 0;
    
    // Called to select a thread to run
    virtual std::unique_ptr<Thread> select_thread() = 0;

    // Called when a thread is blocked
    virtual void handle_thread_block(std::unique_ptr<Thread> thread) = 0;

    // Called when a thread is done
    virtual void handle_thread_done(std::unique_ptr<Thread> thread) = 0;

    // Do something during a tick
    virtual void handle_tick() = 0;
};

#endif