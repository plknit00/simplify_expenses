#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Node {
  int index;
  std::vector<Node *> children;
  Node *parent;
};

bool next_node_is_sink(int source_index, int sink_index,
                       std::vector<std::vector<float>> transactions,
                       Node *&root);

void add_edges(Node *parent, std::queue<Node *> &queue,
               std::vector<std::vector<float>> transactions, Node *source);

void maxflow(int source_index, int sink_index,
             std::vector<std::vector<float>> &transactions,
             std::vector<std::vector<float>> &residual_transactions);

std::vector<std::vector<float>> compute_optimized_transactions(
    std::vector<std::vector<float>> transactions);

void print_output(std::vector<std::string> names,
                  std::vector<std::vector<float>> residual_transactions,
                  std::string output_file);