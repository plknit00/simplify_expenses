#include "simplify.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

// should I use a different kind of pointer??
// every node only has one parent pointer besides sink??
// might work out ok though
struct Node {
  int index;
  std::vector<Node *> children;
  Node *parent;
};

// adds sink node to level graph if an edge for it exists
// between the current element
// returns true if edge exists in curr->sink direction, false otherwise
bool next_node_is_sink(int curr_elt_index, int sink_index,
                       std::vector<std::vector<float>> transactions,
                       Node *&root) {
  float curr_sink_trans_value;
  // look if there exists edge between curr_elt and sink
  if (curr_elt_index < sink_index) {
    curr_sink_trans_value = transactions[curr_elt_index][sink_index];
  } else {
    curr_sink_trans_value = transactions[sink_index][curr_elt_index];
  }
  if (curr_sink_trans_value > 0) {
    Node *child = new Node;
    child->index = sink_index;
    root->children.push_back(child);
    return true;
  }
  return false;
}

// can i make transactions const?
// adds all edges from the current node where they owe someone else
void add_edges(Node *parent, std::queue<Node *> &queue,
               std::vector<std::vector<float>> transactions, Node *source) {
  int size = transactions.size();
  int parent_index = parent->index;
  float amount;
  for (int index = 0; index < size; index++) {
    if (parent_index < index) {
      amount = transactions[parent_index][index];
    } else if (parent_index > index) {
      amount = transactions[index][parent_index];
    } else {
      // case where parent_index = index
      amount = 0;
    }
    // check that there exists nonzero edge between these nodes
    if (amount > 0) {
      // check that this is not looping back within its path
      // not sure if this is the logic I want
      bool repeat = false;
      Node *ptr = parent;
      while (ptr != nullptr || ptr->index != source->index) {
        if (index == ptr->index) {
          repeat = true;
          break;
        }
        if (ptr->parent != nullptr) {
          ptr = ptr->parent;
        } else {
          break;
        }
      }
      if (!repeat) {
        Node *child = new Node;
        child->index = index;
        parent->children.push_back(child);
      }
    }
  }
}

void maxflow(int source_index, int sink_index,
             std::vector<std::vector<float>> &transactions,
             std::vector<std::vector<float>> &optimized_transactions) {
  //  Step 1: use bfs to construct a level graph from source to sink
  std::queue<Node *> queue;
  std::vector<int> visited_indecies;
  int size = transactions.size();
  // initialize residual graph with depth 1 and root = source
  int depth = 1;
  Node *source = new Node;
  source->index = source_index;
  // queue.push(source);
  // conduct bfs to create level graphs at increasing depths
  // stop when the depth is equal to the number of people????
  while (depth < size) {
    // construct level graph of depth current depth
    Node *curr_node;
    int curr_index;
    source->index = source_index;
    queue.push(source);
    // run bfs for a given depth
    while (!queue.empty()) {
      curr_node = queue.front();
      curr_index = curr_node->index;
      visited_indecies.push_back(curr_index);
      if (depth > 1) {
        add_edges(curr_node, queue, transactions, source);
      }
      /*for (int i = 0; i < transactions.size(); i++) {
        auto end = visited_indecies.end();
        bool index_not_found =
            (std::find(visited_indecies.begin(), end, i) == end);
        if ((transactions[curr_index][i] != 0) && (index_not_found)) {
          queue.push(i);
        }
      }*/
    }
    next_node_is_sink(curr_index, sink_index, transactions, curr_node);
    // find blocking flow on current graph
    // update edges of transactions
    // update new edges in opt_trans
    depth++;
  }
}

std::vector<std::vector<float>> compute_optimized_transactions(
    std::vector<std::vector<float>> transactions) {
  std::vector<std::vector<float>> optimized_transactions;
  int num_people = transactions.size();
  // initialize optimized transaction matrix to all zeros
  // can make matrix initializer a helper function instead ******
  optimized_transactions.reserve(num_people);
  for (int i = 0; i < num_people; i++) {
    std::vector<float> trans_row;
    trans_row.reserve(num_people);
    optimized_transactions.push_back(trans_row);
    for (int j = 0; j < num_people; j++) {
      optimized_transactions[i].push_back(0);
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
      maxflow(source, sink, transactions, optimized_transactions);
    }
  }
  return optimized_transactions;
}

void print_output(std::vector<std::string> names,
                  std::vector<std::vector<float>> residual_transactions,
                  std::string output_file) {
  // do stuff
}