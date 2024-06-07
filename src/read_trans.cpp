#include "read_trans.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

std::vector<std::vector<float>> read_input(std::string input_file,
                                           std::vector<std::string> &names) {
  std::string input_garbage;
  std::ifstream myfile;
  int num_people, num_trans;
  std::vector<std::vector<float>> transactions;
  myfile.open(input_file);

  // read the number of people and transactions in file
  myfile >> num_people >> input_garbage >> num_trans >> input_garbage;

  // initialize transaction matrix to all zeros
  transactions.reserve(num_people);
  for (int i = 0; i < num_people; i++) {
    std::vector<float> trans_row;
    trans_row.reserve(num_people);
    transactions.push_back(trans_row);
    for (int j = 0; j < num_people; j++) {
      transactions[i].push_back(0);
    }
  }

  // fill out transaction matrix based on input
  for (int i = 0; i < num_trans; i++) {
    std::string person_paying;
    std::string person_recieving;
    bool person_pay_found = false;
    bool person_recieve_found = false;
    bool person_pay_index;
    bool person_recieve_index;
    std::string string_amount;
    float amount;
    myfile >> person_paying >> input_garbage >> person_recieving >>
        input_garbage;
    // remove the $ and . characters from the amount string
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
        break;
      }
    }
    // pay and recieve index must always be different
    if (!person_pay_found) {
      person_pay_index = names.size();
      names.push_back(person_paying);
    }
    if (!person_recieve_found) {
      person_pay_index = names.size();
      names.push_back(person_recieving);
    }
    // update directed graph to have this transaction
    // choose the person with the lowest index to be the row value
    // we want to ensure this matrix is upper triangular
    // and the sign of the amount indicates which direction owing goes in
    if (person_pay_index < person_recieve_index) {
      transactions[person_pay_index][person_recieve_index] += amount;
    } else
      transactions[person_recieve_index][person_pay_index] -= amount;
  }

  myfile.close();
  return transactions;
}