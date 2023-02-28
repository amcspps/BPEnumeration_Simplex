#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Taskloader.h"
#include "vector_t.h"
#include "task.h" 
using namespace std;

int main()
{
	TaskLoader mom;
	auto [task, cond, ineq] = mom.load("C:\\more\\University\\cpp\\BPE\\task.txt");

	std::cout << "canon: -----------------------------------------------------" << endl;
	
	cout << "    straight task:" << endl;
	mom.printTask(task, ineq);
	
	cout << "    straight canonical task:" << endl;
	task_t canon = mom.makeCanon(task, cond, ineq);
	mom.printTask(canon, {});
	
	Task ct = Task(canon.A, canon.b, canon.F);
	ct.boundary_point_enumeration(CANONIC);
	//mom.forSimplecs(canon);

	std::cout << "\n dual: -----------------------------------------------------" << std::endl;
	cout << "    dual task:" << endl;
	task_t dual = mom.makeDual(task, cond, ineq);
	cout << "    dual canonical task:" << endl;
	mom.printTask(dual, {});

	//cout << "    dual canonical task:" << endl;
	//task_t canon = mom.makeCanon(task, cond, ineq);
	//mom.printTask(canon);
	
	Task dt = Task(dual.A, dual.b, dual.F);
	dt.boundary_point_enumeration(DUAL);
	//mom.forSimplecs(dual);
	return 0;
}
