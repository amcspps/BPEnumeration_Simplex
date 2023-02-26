#include <iostream>
#include "TaskLoader.h"
using namespace std;

int main()
{
	TaskLoader mom;
	auto [task, cond, ineq] = mom.load("C:\\more\\University\\cpp\\BPE\\task.txt");
	std::cout << "canon:" << std::endl << std::endl;
	TaskLoader::printTask(mom.makeCanon(task, cond, ineq));
	std::cout << "dual:" << std::endl;
	TaskLoader::printTask(mom.makeDual(task, cond, ineq));
	cout << "Hello CMake." << endl;
	return 0;
}
