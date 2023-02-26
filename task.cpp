#include "task.h"
#include "functions.h"
#include <algorithm>

using namespace std;

void Task::boundary_point_enumeration() {
	vector <double> obj_fun_values;
	set<int> column_set;
	generate_n(inserter(column_set, column_set.end()), _A.cols, [n = 0]() mutable { return n++; });
	vector<set<int>> combinations = generate_combinations(column_set, _A.rows);
	
	for (auto combination : combinations) {
		Matrix submatrix = Matrix(_A, combination);
		obj_fun_values.push_back(evaluate(_C, solve(submatrix, _B), combination));
	}
	cout << "the maximum of objective function is: " << *(max_element(obj_fun_values.begin(), obj_fun_values.end())) << endl;
};



void Task::simplex_method() {};



