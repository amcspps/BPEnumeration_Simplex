#include "functions.h"
#include <algorithm>

using namespace std;


Matrix rotate_upper_triangle(Matrix A) {
	double C, S;
	for (int i = 0; i < A.cols - 1; i++) {
		for (int m = i + 1; m < A.cols; m++) {
			C = A(i, i) / sqrt(A(i, i) * A(i, i) + A(m, i) * A(m, i));
			S = A(m, i) / sqrt(A(i, i) * A(i, i) + A(m, i) * A(m, i));
			for (int k = i; k < A.cols; k++) {
				double A1 = C * A(i, k) + S * A(m, k);
				double A2 = C * A(m, k) - S * A(i, k);
				A(i, k) = A1;
				A(m, k) = A2;
			}
		}
	}
	return A;
}

vector <double> gaussian_reverse(Matrix A, vector_t B) {
	vector<double> X(B.size());
	for (int i = A.cols - 1; i >= 0; i--) {
		double beta = B[i];
		for (int j = A.cols - 1; j > i; j--)
			beta -= A(i, j) * X[j];
		X[i] = beta / A(i, i);
	}

	return X;
};
vector <double> solve(Matrix A, vector_t B) {
	Matrix A_rt = rotate_upper_triangle(A);
	return gaussian_reverse(A_rt, B);
};

double determinant(Matrix A, vector_t B) {
	double det = 1;
	if (A.rows != A.cols) {
		throw std::invalid_argument("matrix is not square");
	}
	Matrix rt = rotate_upper_triangle(A);
	for (int i = 0; i < A.cols; i++) {
		det *= A(i, i);
	}
	return det;
}


double evaluate(vector_t obj_function, vector<double> solution, set<int> variable_indices) {
    double result_value = 0;
    reverse(solution.begin(), solution.end());
    for (auto index : variable_indices) {
		result_value += obj_function[index] * (*solution.end());
		solution.pop_back();
    }
	return result_value;
}

vector<set<int>> generate_combinations(set<int> column_set, int k) {
	vector<set<int>> combinations;
	vector<int> current_permutation(column_set.begin(), column_set.end());
	do {
		set<int> combination(current_permutation.begin(), current_permutation.end() + k);
		if (auto it = find(combinations.begin(), combinations.end(), combination) == combinations.end()) {
			combinations.push_back(combination);
		}
	} while (next_permutation(current_permutation.begin(), current_permutation.end()));
	return  combinations;

}
