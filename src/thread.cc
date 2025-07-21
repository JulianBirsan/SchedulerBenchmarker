#include <stdlib.h>

#include "thread.h"

Thread::Thread(
    int id, 
    int remaining_run_time,
    double block_chance, 
    int avg_block_duration, 
    int sd_block_duration,
    int arrival_time
) :
    id{id},
    remaining_run_time{remaining_run_time},
    block_chance{block_chance},
    avg_block_duration{avg_block_duration},
    sd_block_duration{sd_block_duration},
    arrival_time{arrival_time},
    state{ThreadState::READY} {}

int Thread::get_id() const {
    return id;
}

ThreadState Thread::get_state() const {
    return state;
}

int Thread::get_arrival_time() const {
    return arrival_time;
}

void Thread::make_ready() {
    state = ThreadState::READY;
}

bool Thread::should_block() const {
    return (rand() / (double)RAND_MAX) < block_chance;
}

int Thread::get_block_time() const {
    int sgn = (rand() % 2) == 0 ? 1 : -1;
    return avg_block_duration + sgn * rand() % sd_block_duration;
}

void Thread::preempt() {
    make_ready();
}

void Thread::run() {
    if (should_block()) {
        state = ThreadState::BLOCKED;
    } else {
        remaining_run_time--;
        if (remaining_run_time == 0) {
            state = ThreadState::TERMINATED;
        }
    }
}

