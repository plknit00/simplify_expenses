#include "simplify.h"

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
             std::vector<std::vector<float>> &residual_transactions) {
  // will work as bfs between two edges and there cannot be
  // cycles or repeatedly visited indecies within a path
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
    // has with other indices, check no index is visited twice
    // within a path or else loops and cycles are created
    // is the looping correct ???
    for (int i = 0; i < transactions.size(); i++) {
      // somehow need to make sure visited incides are unique to each path
      // but not necessarily in general?
      // how to store each path separately????
      auto end = visited_indecies.end();
      bool index_not_found =
          (std::find(visited_indecies.begin(), end, i) == end);
      if ((transactions[curr_index][i] != 0) && (index_not_found)) {
        queue.push(i);
      }
      // also check how sign of transaction amount comes into play
    }
  }

  // step 1 dinics
  //  find a blocking flow
  //  dinic flow must be able to be undone
  //  augmented graph
}

std::vector<std::vector<float>> compute_residual(
    std::vector<std::vector<float>> transactions) {
  std::vector<std::vector<float>> residual_transactions;
  int num_people = transactions.size();
  // initialize residual transaction matrix to all zeros
  transactions.reserve(num_people);
  for (int i = 0; i < num_people; i++) {
    std::vector<float> trans_row;
    trans_row.reserve(num_people);
    transactions.push_back(trans_row);
    for (int j = 0; j < num_people; j++) {
      transactions[i].push_back(0);
    }
  }

  // row gives the person who owes money
  for (int source = 0; source < num_people; source++) {
    // column gives the person who recieves money
    // sign of amount owed gives direction of edge
    for (int sink = 0; sink < num_people; sink++) {
      // people don't need to pay themselves
      if (source == sink) {
        break;
      }
      int amount = transactions[source][sink];
      if (amount == 0) {
        break;
      }
      // if the amount is negative, flip direction of owing
      if (amount < 0) {
        int temp = source;
        source = sink;
        sink = temp;
      }
      // run dinic's maxflow algorithm
      maxflow(source, sink, transactions, residual_transactions);
      // float curr_trans_amount = transactions[source][sink];
    }
  }

  return residual_transactions;
}

void print_output(std::vector<std::string> names,
                  std::vector<std::vector<float>> residual_transactions,
                  std::string output_file) {
  // do stuff
}