#include "graph.h"
#include "read_trans.h"
#include "simplify.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  std::string input_file = argv[0];
  std::string output_file = argv[1];
  std::vector<std::string> names;
  // Should I calculate net change in cash for each person to see if anyone owes
  // 0 overall before proceeding with maxflow?
  // eventually add dinic's optimization of cutting off dead ends ahead of time
  std::vector<std::vector<float>> transactions = read_input(input_file, names);
  std::vector<std::vector<float>> optimized_transactions =
      compute_optimized_transactions(transactions);
  print_output(names, optimized_transactions, output_file);
  return 0;
}