#include <stdlib.h>

#include "thread.h"

Thread::Thread(
    int id, 
    int remaining_run_time,
    double block_chance, 
    int avg_block_duration, 
    int sd_block_duration
) :
    id{id},
    remaining_run_time{remaining_run_time},
    block_chance{block_chance},
    avg_block_duration{avg_block_duration},
    sd_block_duration{sd_block_duration} {
        state = ThreadState::READY;
    }

int Thread::get_id() const {
    return id;
}

bool Thread::should_block() const {
    return (rand() / (double)RAND_MAX) < block_chance;
}

int Thread::get_block_time() const {
    int sgn = (rand() % 2) == 0 ? 1 : -1;
    return avg_block_duration + sgn * rand() % sd_block_duration;
}

bool Thread::is_complete() const {
    return remaining_run_time <= 0;
}

void Thread::preempt() {
    state = ThreadState::READY;
}

