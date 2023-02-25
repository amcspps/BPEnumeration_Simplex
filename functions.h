#pragma once
#include "matrix_t.h"
#include "vector_t.h"

Matrix rotate_upper_triangle(Matrix A);
std::vector <double> gaussian_reverse(Matrix A, vector_t B);
std::vector <double> solve(Matrix A, vector_t B);
double determinant(Matrix A, vector_t B);
std::vector<std::set<int>> generate_combinations(std::set<int> column_set, int k /*conditions number*/);
double evaluate(vector_t obj_function, std::vector<double> solution, std::set<int> variable_indices);

