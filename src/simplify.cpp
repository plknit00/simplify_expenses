#include "simplify.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

// abstract 2d vector trans matrix to a graph class
// its ok that it just has one member variable
// should be private
// graph edges need to be able to be bidirectional and have different capacity
//

// can make nice gettter functions like
// amount = graph.a_owes_b(index1, index2);

// restructure matrix to not keep track of the boxes
// that will always be empty (waste of space)

// never use vec<vec>>, just use fancy math to index

// should I use a different kind of pointer??
struct Node {
  int index;
  // shared ptr children
  std::vector<Node *> children;
  // weak parents ptrs
  std::vector<Node *> parents;
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
               std::vector<std::vector<float>> transactions, Node *source,
               std::vector<int> visited_indecies) {
  int size = transactions.size();
  int parent_index = parent->index;
  float amount;
  // abstraction a_owes_b
  // does the weird cases for me (not in this function)
  // a never owes a
  for (int index = 0; index < size; index++) {
    // one case needs to be negated !!!!
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
      int curr_index = parent->index;
      auto repeat =
          find(visited_indecies.begin(), visited_indecies.end(), curr_index);
      if (repeat != visited_indecies.end()) {
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
  int size = transactions.size();
  // initialize residual graph with depth 1 and root = source
  int depth = 1;
  // avoid new if possible
  // use smart pointers instead to auto clean memory
  std::shared_ptr<Node> source = std::make_shared<Node>();
  source->index = source_index;
  float new_edge_amt = 0;
  // conduct bfs to create level graphs at increasing depths
  // stop when the depth is equal to the number of people????
  // when can we stop early??
  // end when no more level graphs can be constructed to sink
  // have level graph making function have some sort of fail that returns
  // for this condition
  while (depth < size) {
    // construct new level graph of depth current depth
    new_edge_amt = 0;
    std::queue<std::shared_ptr<Node>> queue;
    std::vector<int> visited_indecies;
    std::shared_ptr<Node> curr_node;
    int curr_index;
    queue.push(source);
    // run bfs for a given depth to construct level graph
    while (!queue.empty()) {
      curr_node = queue.front();
      curr_index = curr_node->index;
      visited_indecies.push_back(curr_index);
      if (depth > 1) {
        add_edges(curr_node, queue, transactions, source, visited_indecies);
      }
    }
    next_node_is_sink(curr_index, sink_index, transactions, curr_node);
    // find blocking flow on current graph
    // update backward edges?
    // update edges of transactions
    // update new edges in opt_trans
    // depth++;
    // lines 110 - 129 new function
    //
  }
  // add edge btw src and sink on opt mtrx by new_edge_amt
  optimized_transactions[source_index][sink_index] += new_edge_amt;
  // make sure orig trans mtrx is updates with lesser edge values
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
  for (int source = 1; source < num_people - 1; source++) {
    // column gives the person who recieves money
    // sign of amount owed gives direction of edge
    for (int sink = source + 1; sink < num_people; sink++) {
      // people don't need to pay themselves
      if (source == sink) {
        // this case should never be reached, delete later
        std::cout << "source = sink case, fix indecies" << std::endl;
        break;
      }
      int amount = transactions[source][sink];
      // case where no edge exists, do nothing
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