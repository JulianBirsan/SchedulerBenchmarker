#include "round_robin.h"

RoundRobin::RoundRobin(int quantum) : quantum{quantum}, remaining{quantum} {}

void RoundRobin::handle_new_thread(std::shared_ptr<Thread> thread) {
    queue.push(thread);
}

std::shared_ptr<Thread> RoundRobin::select_thread() {
    if (queue.empty()) return nullptr;
    std::shared_ptr<Thread> chosen = queue.front();
    queue.pop();
    remaining = quantum;
    return chosen;
}

void RoundRobin::handle_tick(std::shared_ptr<Thread> current_thread) {
    if (current_thread) {
        remaining--;
        if (remaining == 0) {
            current_thread->preempt();
            queue.push(current_thread);
        }
    }
}