#include "simulator.h"
#include <queue>
#include <algorithm>

Result simulate_fcfs(std::vector<Process> procs) {
    std::sort(procs.begin(), procs.end(), [](auto& a, auto& b){
        if (a.arrival != b.arrival) return a.arrival < b.arrival;
        return a.pid < b.pid;
    });
    for (auto& p : procs) p.remaining = p.burst;

    std::queue<int> ready;
    int time = 0, i = 0, idle = 0, completed = 0, n = (int)procs.size(), current = -1;

    auto admit = [&]() {
        while (i < n && procs[i].arrival <= time) { ready.push(i++); }
    };

    while (completed < n) {
        admit();
        if (current == -1) {
            if (ready.empty()) {
                int nextA = procs[i].arrival;
                idle += (nextA - time);
                time = nextA;
                admit();
            }
            if (!ready.empty()) {
                current = ready.front(); ready.pop();
                if (procs[current].start_time == -1) procs[current].start_time = time;
            }
        }
        // run to completion
        int run = procs[current].remaining;
        time += run;
        procs[current].remaining = 0;
        procs[current].completion = time;
        completed++;
        current = -1;
    }

    Result r;
    r.procs = std::move(procs);
    r.makespan = time;
    r.idle_time = idle;
    return r;
}
