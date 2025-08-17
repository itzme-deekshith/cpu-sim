#include "io.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Process> load_csv(const std::string& filename) {
    std::vector<Process> processes;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return processes;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        int pid, arrival, burst, priority;
        char comma;

        if (ss >> pid >> comma >> arrival >> comma >> burst >> comma >> priority) {
            Process p{pid, arrival, burst, priority, burst}; // remaining = burst
            processes.push_back(p);
        }
    }
    return processes;
}

void print_result(const Result& result) {
    std::cout << "PID\tArrival\tBurst\tPriority\tStart\tCompletion\tWaiting\tTurnaround\n";

    int total_waiting = 0;
    int total_turnaround = 0;

    for (const auto& p : result.procs) {
        int turnaround = p.completion - p.arrival;
        int waiting = turnaround - p.burst;

        total_waiting += waiting;
        total_turnaround += turnaround;

        std::cout << p.pid << "\t"
                  << p.arrival << "\t"
                  << p.burst << "\t"
                  << p.priority << "\t\t"
                  << p.start_time << "\t"
                  << p.completion << "\t\t"
                  << waiting << "\t"
                  << turnaround << "\n";
    }

    int n = result.procs.size();
    if (n > 0) {
        std::cout << "\nAverage Waiting Time: " 
                  << (double)total_waiting / n << "\n";
        std::cout << "Average Turnaround Time: " 
                  << (double)total_turnaround / n << "\n";
    }

    std::cout << "Makespan: " << result.makespan << "\n";
    std::cout << "CPU Idle Time: " << result.idle_time << "\n";
}
