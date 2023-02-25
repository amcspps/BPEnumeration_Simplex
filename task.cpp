#include "task.h"
#include "functions.h"
#include <algorithm>

using namespace std;



void Task::boundary_point_enumeration() {
	vector <vector<double>> obj_fun_values;
	set<int> column_set;
	generate_n(inserter(column_set, column_set.end()), _A.cols, [n = 0]() mutable { return n++; });
	vector<set<int>> combinations = generate_combinations(column_set, _A.rows);
	
	for (auto combination : combinations) {
		Matrix submatrix = Matrix(_A, combination);
		//obj_fun_values.push_back(solve(_A, _B));
	}
};



void Task::simplex_method() {};



