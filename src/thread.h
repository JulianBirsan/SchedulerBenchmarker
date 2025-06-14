#ifndef THREAD_H
#define THREAD_H

enum class ThreadState { READY, RUNNING, BLOCKED, TERMINATED };

// Interface for a thread
class Thread {
private:
    // unique identifier of thread
    int id;
    // remaining time that this thread needs to run
    int remaining_run_time;
    // probability for thread to block in a time slice 
    double block_chance;
    // the average time for thread to block
    int avg_block_duration;
    // the standard deviation of time a thread blocks
    int sd_block_duration;
    // the state of the thread
    ThreadState state;
    // the arrival time of the thread
    int arrival_time;

    // computes if thread should block in this time slice
    bool should_block() const;

public:
    Thread(
        int id, 
        int remaining_run_time, 
        double block_chance, 
        int avg_block_duration, 
        int sd_block_duration,
        int arrival_time
    );

    // getter for id
    int get_id() const;

    // getter for state
    ThreadState get_state() const;

    // getter for arrival time
    int get_arrival_time() const;

    // makes thread in ready state
    void make_ready();

    // computes block time for thread
    int get_block_time() const;

    // preempt this thread
    void preempt();

    // run thread for one time slice
    void run();
};

#endif