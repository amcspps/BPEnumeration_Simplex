#pragma once
#include "matrix_t.h"
#include "vector_t.h"
class Task {
public:
	Task(Matrix A, vector_t B, vector_t C);
	void format_data();
	void rotations_method();
	void boundary_point_enumeration();
	void simplex_method();
	/*antother functions to process data if needed*/
	void print();
private:
	Matrix _A;
	vector_t _B;
	vector_t _C;
	

};