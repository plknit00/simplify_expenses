#include "graph.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

class Graph {
 public:
  void set_input_file(std::string input_f) {
    input_file = input_f;
  }

  void set_output_file(std::string output_f) {
    output_file = output_f;
  }

  // create graph based on number of people
  // initialize all transaction amounts to $0
  void create_graph(int num_people) {
    int num_possible_transactions = ((num_people) * (num_people - 1)) / 2;
    transactions.reserve(num_possible_transactions);
    for (int i = 0; i < num_people; i++) {
      // transactions[i].push_back(0);
    }
  }

  // read graph metadata
  int read_metadata_input(std::ifstream &infile) {
    std::string input_garbage;
    int num_trans;
    infile >> num_people >> input_garbage >> num_trans >> input_garbage;
    return num_trans;
  }

  // read transactions from input file
  void read_transactions(int num_trans, std::ifstream &infile) {
    std::string input_garbage;
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
      infile >> person_paying >> input_garbage >> person_recieving >>
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
        std::cout << "test";
        // transactions[person_pay_index][person_recieve_index] += amount;
      } else {
        std::cout << "test";
        // transactions[person_recieve_index][person_pay_index] -= amount;
      }
    }
  }

  void read_input() {
    std::ifstream infile;
    infile.open(input_file);
    int num_trans = read_metadata_input(infile);
    read_transactions(num_trans, infile);
    infile.close();
  }

  // convert between [][] to vector indecies
  int index_convert(int source_index, int sink_index) {
    int transaction_index;
    if (source_index > sink_index) {
      int temp = source_index;
      source_index = sink_index;
      sink_index = temp;
    }
    int val1 = 0;
    if (source_index >= 0) {
      for (int i = 1; i < source_index; i++) {
        val1 += num_people - i;
      }
    }
    int val2 = sink_index - 1;
    transaction_index = val1 + val2;
    return transaction_index;
  }

  // get amount that one person owes another
  float source_owes_sink(int source_index, int sink_index) {
    int index = index_convert(source_index, sink_index);
    return transactions[index];
  }

 private:
  std::vector<float> transactions;
  std::vector<std::string> names;
  std::string input_file;
  std::string output_file;
  int num_people;
};