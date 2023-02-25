#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "TaskLoader.h"
using namespace std;

int main()
{
	TaskLoader dad;
	dad.load("task.txt");
	cout << "Hello CMake." << endl;
	return 0;
}
