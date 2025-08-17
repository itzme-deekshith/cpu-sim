#include "simulator.h"
#include <queue>
#include <algorithm>

struct SJFCompare {
    const std::vector<Process>* procs;
    bool operator()(int a, int b) const {
        if ((*procs)[a].burst != (*procs)[b].burst)
            return (*procs)[a].burst > (*procs)[b].burst; // smaller burst first
        if ((*procs)[a].arrival != (*procs)[b].arrival)
            return (*procs)[a].arrival > (*procs)[b].arrival;
        return (*procs)[a].pid > (*procs)[b].pid;
    }
};

Result simulate_sjf(std::vector<Process> procs) {
    std::sort(procs.begin(), procs.end(), [](auto& a, auto& b){
        if (a.arrival != b.arrival) return a.arrival < b.arrival;
        return a.pid < b.pid;
    });
    for (auto& p : procs) p.remaining = p.burst;

    int n = (int)procs.size(), i = 0, completed = 0, time = 0, idle = 0;
    std::priority_queue<int, std::vector<int>, SJFCompare> ready{SJFCompare{&procs}};

    auto admit = [&]() {
        while (i < n && procs[i].arrival <= time) { ready.push(i++); }
    };

    while (completed < n) {
        admit();
        if (ready.empty()) {
            int nextA = procs[i].arrival;
            idle += (nextA - time);
            time = nextA;
            admit();
        }
        int current = ready.top(); ready.pop();
        if (procs[current].start_time == -1) procs[current].start_time = time;

        int run = procs[current].remaining;
        time += run;
        procs[current].remaining = 0;
        procs[current].completion = time;
        completed++;
    }

    Result r;
    r.procs = std::move(procs);
    r.makespan = time;
    r.idle_time = idle;
    return r;
}
