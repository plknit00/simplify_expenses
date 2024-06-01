#include "print_csi.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
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
    // choose the person with the lowest index to be the row value
    // we want to ensure this matrix is upper triangular
    // and the sign of the amount indicates which direction owing goes in
    if (person_pay_index < person_recieve_index) {
      transactions[person_pay_index][person_recieve_index] += amount;
    } else
      // check that this covers all cases and works correctly
      transactions[person_recieve_index][person_pay_index] -= amount;
  }

  myfile.close();
  return transactions;
}

void maxflow(int source, int sink,
             std::vector<std::vector<float>> &transactions,
             std::vector<std::vector<float>> &residual_transactions) {
  // will work as bfs between two edges and there cannot be
  // cycles or repeatedly visited numbers
  std::vector<int> visited_indecies;
  std::queue<int> queue;
  int curr_index;
  queue.push(source);
  while (!queue.empty()) {
    curr_index = queue.front();
    visited_indecies.push_back(curr_index);
    if (curr_index == sink) {
      break;
    }
    // add to queue by checking all possible transactions curr_index
    // has with other indices, check no index is visited twice or else
    // loops and cycles are created
    for (int i = 0; i < transactions.size(); i++) {
      // somehow need to make sure visited incides is unique to each path?
      // how to store each path separately????
      bool index_not_found =
          (std::find(visited_indecies, i) == visited_indecies.end());
      if ((transactions[curr_index][i] != 0) && (index_not_found)) {
        queue.push(i);
      }
    }
  }
}

std::vector<std::vector<float>>
compute_residual(std::vector<std::vector<float>> transactions) {
  int size = transactions.size();

  std::vector<std::vector<float>> residual_transactions;
  // initialize residual transaction matrix to all zeros
  transactions.reserve(size);
  for (int i = 0; i < size; i++) {
    std::vector<float> trans_row;
    trans_row.reserve(size);
    transactions.push_back(trans_row);
    for (int j = 0; j < size; j++) {
      transactions[i].push_back(0);
    }
  }

  int size = transactions.size();
  // row gives the person who owes money
  for (int source = 0; source < size; source++) {
    // column gives the person who recieves money
    // sign of amount owed gives direction of edge
    for (int sink = 0; sink < size; sink++) {
      // people don't need to pay themselves
      if (source == sink) {
        break;
      }
      // run dinic's maxflow algorithm
      maxflow(source, sink, transactions, residual_transactions);
      // float curr_trans_amount = transactions[source][sink];
    }
  }

  return residual_transactions;
}

void store_output() {}

int main(std::string input_file) {
  std::cout << "Hi Remy!" << std::endl;
  std::vector<std::vector<float>> transactions = read_input(input_file);
  std::vector<std::vector<float>> residual_transactions =
      compute_residual(transactions);
  // need names vector for printing output
  // print_output(output_file);
  return 0;
}