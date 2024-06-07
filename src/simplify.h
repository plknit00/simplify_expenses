#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

void maxflow(int source, int sink,
             std::vector<std::vector<float>> &transactions,
             std::vector<std::vector<float>> &residual_transactions);

std::vector<std::vector<float>> compute_residual(
    std::vector<std::vector<float>> transactions);

void print_output(std::vector<std::string> names,
                  std::vector<std::vector<float>> residual_transactions,
                  std::string output_file);