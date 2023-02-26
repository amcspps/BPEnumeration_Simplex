#ifndef TASK_H_
#define TASK_H_
#pragma once
#include<iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <tuple>
#include "matrix_t.h"
#include "vector_t.h"

struct task_t {
    Matrix A;
    vector_t b;
    vector_t F;
};

class TaskLoader {
public:
    std::tuple<task_t, std::vector<int>, std::vector<int>> load(std::string filename);
    task_t makeCanon(task_t M, std::vector<int> conditions, std::vector<int> inequality);
    task_t makeDual(task_t M, std::vector<int> conditions, std::vector<int> inequality);
    static void printTask(task_t M);
};
#endif //TASK_H_