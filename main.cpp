#include "print_csi.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

std::vector<std::string> read_input(std::string input_file) {
  std::string input;
  std::ofstream myfile;
  int num_people;
  int num_trans;
  myfile.open(input_file);

  // read the number of people in file
  getline(myfile, num_people, " ");
  // read info we don't need to store
  getline(myfile, " ");
  // read the number of lines in file
  getline(myfile, num_trans, " ");
  // read info we don't need to store
  getline(myfile, " ");

  for (int i = 0; i < num_trans; i++) {
    getline(myfile);
    // start to build directed graph for info
  }

  myfile.close();
  return input;
}

void store_output() {}

int main(std::string input_file) {
  std::cout << "Hi Remy!" << std::endl;
  std::vector<std::string> input = read_input(input_file);
  return 0;
}