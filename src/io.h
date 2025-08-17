#pragma once
#include <vector>
#include <string>
#include "simulator.h"

std::vector<Process> load_csv(const std::string& filename);
void print_result(const Result& result);
