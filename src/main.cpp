#include "simulator.h"
#include "schedulers/fcfs.h"
#include "schedulers/sjf.h"
#include "io.h"
#include <iostream>

int main() {
    auto procs = load_csv("data/p1.csv");

    // Run FCFS
    SimConfig cfg_fcfs{Alg::FCFS};
    auto result_fcfs = simulate(procs, cfg_fcfs);
    std::cout << "\n--- FCFS Results ---\n";
    print_result(result_fcfs);

    // Run SJF
    SimConfig cfg_sjf{Alg::SJF};
    auto result_sjf = simulate(procs, cfg_sjf);
    std::cout << "\n--- SJF Results ---\n";
    print_result(result_sjf);

    return 0;
}
