#include "task.h"
#include "functions.h"
#include <algorithm>

using namespace std;

void Task::boundary_point_enumeration() {
	cout << "---------------------------------------------------------" << endl;
	vector <double> obj_fun_values;
	vector <vector<double>> boundary_points;
	vector<set<int>> solution_variables_indices;
	set<int> column_set;
	generate_n(inserter(column_set, column_set.end()), _A.cols, [n = 0]() mutable { return n++; });
	vector<set<int>> combinations = generate_combinations(column_set, _A.rows);
	
	for (auto combination : combinations) {
		Matrix submatrix = Matrix(_A, combination);
		auto sol = solve(submatrix, _B);
		if (sol != vector<double>{BAD_DETERMINANT} && sol > 0) {
			boundary_points.push_back(sol);
			obj_fun_values.push_back(evaluate(_C, sol, combination));
			solution_variables_indices.push_back(combination);
			cout << "submatrix:" << endl <<submatrix << endl;
			cout << "objective function value: " << evaluate(_C, sol, combination) << endl;
			cout << "solution:" << combination << "=" << sol << ", other x_i = 0" << endl;
			cout << "---------------------------------------------------------" << endl;
		}
	}
	auto val = *(max_element(obj_fun_values.begin(), obj_fun_values.end()));
	auto index = find_index(obj_fun_values, val);
	cout << "the maximum of objective function is: " << val<< "\t"<< "variables are:" << solution_variables_indices[index]<< "=" << boundary_points[index] << ", other x_i = 0"  << endl;
};



void Task::simplex_method() {};



