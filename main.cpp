#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "matrix_t.h"
#include "Taskloader.h"
#include "vector_t.h"
#include "task.h" 
using namespace std;

int main()
{
	TaskLoader mom;
	auto [task, cond, ineq] = mom.load("C:\\Users\\kachok na masse\\source\\repos\\BPEnumeration_Simplex\\task.txt");

	std::cout << "canon: -----------------------------------------------------";
	task_t canon = mom.makeCanon(task, cond, ineq);
	Task ct = Task(canon.A, canon.b, canon.F);
	ct.boundary_point_enumeration();
	mom.forSimplecs(canon);

	std::cout << "dual: -----------------------------------------------------" << std::endl;
	task_t dual = mom.makeDual(task, cond, ineq);
	Task dt = Task(canon.A, canon.b, canon.F);
	mom.forSimplecs(dual);
	return 0;
}
