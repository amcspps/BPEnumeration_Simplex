#pragma once
#include "vector_t.h"

#define CANONIC -3
#define DUAL -4
class Task /*notice that task might be a problem in a straight or dual forms. */ {
public:
	Task(Matrix& A, vector_t& B, vector_t& C) : _A(A), _B(B), _C(C), _sol(0) {};
	void boundary_point_enumeration(int task_type);
	void simplex_method();
private:
	vector_t _C;//object function
	Matrix _A;//constraints matrix 
	vector_t _B;//rhs column
	vector_t _sol;//solution
};