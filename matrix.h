#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;


class matrix
{
  int row_length;
  int column_length;
  vector<vector<string>> basemap;

public:
  matrix(vector<vector<string>> inputmap);
  void printbasemap();
  void printvector(vector<std::vector<long double>> vec);
  vector<long double> multiply_matrix(vector<std::vector<long double>> A, std::vector<long double> B);
  vector<long double> multiply_vector(vector<long double> vec1,vector<long double> vec2);
  

};

#endif