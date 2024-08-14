#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

class Graph {
 private:
  std::vector<float> transactions;
  std::vector<std::string> names;
  std::string input_file;
  std::string output_file;
  int num_people;

 public:
  void set_input_file(std::string input_f);

  void set_output_file(std::string output_f);

  // create graph based on number of people
  // initialize all transaction amounts to $0
  void create_graph();

  // read graph metadata
  int read_metadata_input(std::ifstream &infile);

  // read transactions from input file
  void read_transactions(int num_trans, std::ifstream &infile);

  void read_input();

  // convert between [][] to vector indecies
  int index_convert(int source_index, int sink_index);

  // get amount that one person owes another
  float source_owes_sink(int source_index, int sink_index);
};