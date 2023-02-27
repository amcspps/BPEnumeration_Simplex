#include <iostream>
#include "TaskLoader.h"
using namespace std;

int main()
{
	TaskLoader mom;
	auto [task, cond, ineq] = mom.load("C:\\more\\University\\cpp\\BPE\\task.txt");

	std::cout << "canon:";
	task_t canon = mom.makeCanon(task, cond, ineq);
	TaskLoader::printTask(canon);
	std::cout << std::endl;
	mom.forSimplecs(canon);

	std::cout << "dual:" << std::endl;
	task_t dual = mom.makeDual(task, cond, ineq);
	TaskLoader::printTask(dual);
	std::cout << std::endl;
	mom.forSimplecs(dual);
	return 0;
}
