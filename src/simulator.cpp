#include "simulator.h"

Result simulate_fcfs(std::vector<Process> procs);
Result simulate_sjf(std::vector<Process> procs);

Result simulate(std::vector<Process> procs, const SimConfig& cfg) {
    switch (cfg.alg) {
        case Alg::FCFS:
            return simulate_fcfs(procs);
        case Alg::SJF:
            return simulate_sjf(procs);
        default:
            return Result{};
    }
}
