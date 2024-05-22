#include "print_csi.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

std::vector<std::vector<float>> read_input(std::string input_file) {
  std::string input;
  std::ofstream myfile;
  int num_people;
  int num_trans;
  std::vector<std::string> names;
  std::vector<std::vector<float>> transactions;
  myfile.open(input_file);

  // read the number of people in file
  getline(myfile, num_people, " ");
  // read info we don't need to store
  getline(myfile, " ");
  // read the number of lines in file
  getline(myfile, num_trans, " ");
  // read info we don't need to store
  getline(myfile, "\n");

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
    getline(myfile, person_paying, " ");
    // read info we don't need to store
    getline(myfile, " ");
    // read the name of the person getting money
    getline(myfile, person_recieving, " ");
    // read the amount of money for this transaction
    getline(myfile, string_amount, "\n");
    // remove the $ and . characters from this string
    string_amount.substr(1, string_amount.length() - 2);
    // check string amount is now a valid float value
    if (IsFloat(string_amount)) {
      amount = std::stof(string_amount);
    } else {
      // DO SOMETHING
      // exit entire function and error message
    }
    // check if person paying and person recieving exists in names
    // if they dont, add them, and update their indices
    for (int i = 0; i < names.length(); i++) {
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
    if (!person_paying) {
      person_pay_index = names.length() - 1;
      names.append(person_paying);
    }
    if (!person_recieving) {
      person_pay_index = names.length() - 1;
      names.append(person_recieving);
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