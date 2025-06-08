#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <memory>

#include "thread.h"

class Scheduler {
public:
    virtual ~Scheduler();

    // Called when a new thread is ready
    virtual void handle_new_thread(std::shared_ptr<Thread> thread) = 0;
    
    // Called to select a thread to run
    virtual std::shared_ptr<Thread> select_thread() = 0;

    // Called when a thread is blocked
    virtual void handle_thread_block(std::shared_ptr<Thread> thread) = 0;

    // Called when a thread is done
    virtual void handle_thread_done(std::shared_ptr<Thread> thread) = 0;

    // Do something during a tick, where thread is the current running thread
    virtual void handle_tick(std::shared_ptr<Thread> thread) = 0;
};

#endif