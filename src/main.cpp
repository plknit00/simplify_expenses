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
  // want the input/output files following from main input
  std::string input_file = argv[0];
  std::string output_file = argv[1];
  std::vector<std::string> names;
  // test, delete later
  std::cout << "Hi Remy!" << std::endl;
  // Should I calculate net change in cash for each person to see if anyone owes
  // 0 overall?
  // dinics optimization of cutting off dead ends ahead of time
  std::vector<std::vector<float>> transactions = read_input(input_file, names);
  std::vector<std::vector<float>> residual_transactions =
      compute_residual(transactions);
  // need function between residual and printing?
  // print_output(names, residual_transactions, output_file);
  return 0;
}