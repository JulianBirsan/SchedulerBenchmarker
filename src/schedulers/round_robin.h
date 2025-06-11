#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H
#include <queue>

#include "../scheduler.h"

class RoundRobin: public Scheduler {
private:
    int quantum, remaining;
    std::queue<std::shared_ptr<Thread>> queue;

public:
    RoundRobin(int quantum);
    void handle_new_thread(std::shared_ptr<Thread> thread) override;
    std::shared_ptr<Thread> select_thread() override;
    void handle_tick(std::shared_ptr<Thread> current_thread) override;
};
#endif