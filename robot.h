#ifndef ROBOT_H
#define ROBOT_H
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <numeric>
using namespace std;


class robot
{
vector<double> sensory_error_vector;
int invalid_blocks;
int row_length;
int column_length;
vector<long double> intialvector;
vector<vector<int>> robot_map;
vector<long double> estprobablities;


public:
  robot(int rlen, int clen);
  vector<int>  generate_robot_position(string values, int current_position[2]);
  int total_bitwise_difference(string A, string B);
  void generate_sensory_error(double sensory_error);
  std::vector<std::vector<long double>>  generate_transitivity_matrix(vector<vector<string>> vec);
  void generate_robot_map();
  vector<long double> initial_probability_table(vector<vector<string>> vec);
  vector<long double> generate_objectivity_matrix(vector<vector<string>> basemap, string comparison_string);
  string encode_strings(string directions);
  vector<int> next_state(vector<long double> before_estimation_probablities);
  vector<long double> get_estimation_probablities();
  void clear_estimation_probablities();
};

#endif