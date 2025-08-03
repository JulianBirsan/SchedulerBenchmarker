#ifndef MLFQ_H
#define MLFQ_H

#include <queue>
#include <vector>

#include "../../src/scheduler.h"

class MLFQ : public Scheduler {
public:
    MLFQ(std::vector<int> level_quantums);

    void handle_new_thread(std::shared_ptr<Thread> thread) override;

    std::shared_ptr<Thread> select_thread() override;

    void handle_tick(std::shared_ptr<Thread> current_thread) override;
private:
    int current_level;
    int remaining_time;
    std::vector<std::queue<std::shared_ptr<Thread>>> queues;
    std::vector<int> level_quantums;
};

#endif