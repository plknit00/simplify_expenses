#include "print_csi.h"
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ***************** switch to bazel from cmake ******************
// instructions online

std::vector<std::vector<float>> read_input(std::string input_file) {
  std::string input_garbage;
  std::ifstream myfile;
  int num_people;
  int num_trans;
  std::vector<std::string> names;
  std::vector<std::vector<float>> transactions;
  myfile.open(input_file);

  // read the number of people and transactions in file
  myfile >> num_people >> input_garbage >> num_trans >> input_garbage;

  for (int i = 0; i < num_trans; i++) {
    std::string person_paying;
    bool person_pay_found = false;
    bool person_recieve_found = false;
    bool person_pay_index;
    bool person_recieve_index;
    std::string person_recieving;
    std::string string_amount;
    float amount;
    // read the name of the person owing money
    // read the name of the person getting money
    // read the amount of money for this transaction
    myfile >> person_paying >> input_garbage >> person_recieving >>
        input_garbage;
    // remove the $ and . characters from this string
    string_amount.substr(1, string_amount.length() - 2);
    // check string amount is now a valid float value
    amount = std::stof(string_amount);
    // check if person paying and person recieving exists in names
    // if they dont, add them, and update their indices
    for (int i = 0; i < names.size(); i++) {
      if (names[i] == person_paying) {
        person_pay_found = true;
        person_pay_index = i;
      }
      if (names[i] == person_recieving) {
        person_recieve_found = true;
        person_recieve_index = i;
      }
      if (person_pay_found && person_recieve_found) {
        exit;
      }
    }
    if (!person_pay_found) {
      person_pay_index = names.size() - 1;
      names.push_back(person_paying);
    }
    if (!person_recieve_found) {
      person_pay_index = names.size() - 1;
      names.push_back(person_recieving);
    }
    // update directed graph for transactions
    transactions[person_pay_index][person_recieve_index] = amount;
  }

  myfile.close();
  return transactions;
}

void store_output() {}

int main(std::string input_file) {
  std::cout << "Hi Remy!" << std::endl;
  std::vector<std::vector<float>> input = read_input(input_file);
  return 0;
}