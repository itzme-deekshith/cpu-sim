#pragma once
#include <vector>

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority = 0;
    int remaining;
    int start_time = -1;
    int completion = -1;
};

struct Result {
    std::vector<Process> procs;
    int makespan = 0;
    int idle_time = 0;
};

enum class Alg { FCFS, SJF, SRTF, PRIORITY_NP, PRIORITY_P, RR };

struct SimConfig {
    Alg alg;
    int quantum = 2; // used for RR
};

Result simulate(std::vector<Process> procs, const SimConfig& cfg);
