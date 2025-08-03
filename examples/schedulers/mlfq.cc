#include "mlfq.h"
#include <algorithm>

MLFQ::MLFQ(std::vector<int> level_quantums) 
: current_level{0}, remaining_time{0}, queues{std::vector<std::queue<std::shared_ptr<Thread>>>{}}, level_quantums{level_quantums} {
    for (size_t i = 0; i < level_quantums.size(); i++) {
        queues.push_back(std::queue<std::shared_ptr<Thread>>());
    }
}

void MLFQ::handle_new_thread(std::shared_ptr<Thread> thread) {
    queues[0].push(thread);
}

std::shared_ptr<Thread> MLFQ::select_thread() {
    current_level = 0;
    for(; current_level < static_cast<int>(queues.size()); current_level++) {
        if (!queues[current_level].empty()) {
            std::shared_ptr<Thread> chosen = queues[current_level].front();
            queues[current_level].pop();
            remaining_time = level_quantums[current_level];
            return chosen;
        }
    }
    return nullptr;
}

void MLFQ::handle_tick(std::shared_ptr<Thread> current_thread) {
    if (current_thread) {
        remaining_time--;
        if (remaining_time == 0) {
            current_thread->preempt();
            queues[std::min(current_level + 1, static_cast<int>(queues.size()) - 1)].push(current_thread);
        }
    }
}