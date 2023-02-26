#include "TaskLoader.h"

std::tuple<task_t, std::vector<int>, std::vector<int>> TaskLoader::load(std::string filename) {
    std::ifstream file(filename);
    std::string str;
    std::vector<std::vector<std::string>> linearSystem;
    std::vector<int> conditions;
    std::vector<double> F;

    //read data from the file
    bool nextIter = false;
    int state = 0;

    int M = 0;
    int N = 0;
    std::getline(file, str);
    std::istringstream iss(str);
    iss >> M;
    iss >> N;

    while (std::getline(file, str)) {
        std::vector<std::string> result;
        std::istringstream iss(str);

        for (std::string s; iss >> s; ) {
            result.push_back(s);
        }

        if (state == 0) {
            for (int i = 0; i < result.size(); i++)
                if (result[i] == ">=" || result[i] == "<=" || result[i] == "==") {
                    linearSystem.push_back(result);
                    nextIter = true;
                    break;
                }
            if (nextIter) {
                nextIter = false;
                continue;
            }
            state++;
        }

        if (state == 1) {
            for (int i = 0; i < result.size(); i++)
                conditions.push_back(std::stoi(result[i]));
        }
        else if (state == 2) {
            for (int i = 0; i < result.size(); i++)
                F.push_back(std::stod(result[i]));
        }
        state++;
    }

    Matrix A{ N, M };
    vector_t b{ M };
    std::vector<int> inequality;
    int i = 0;

    for (auto& line : linearSystem) {
        if (line[line.size() - 2] == ">=") {
            for (int j = 0; j < line.size() - 2; j++)
                A.addData(std::stod(line[j]) * (-1), i, j);
            inequality.push_back(i);
            b.addData((-1) * std::stod(line[line.size() - 1]), i++);

        }
        else if (line[line.size() - 2] == "<=") {
            for (int j = 0; j < line.size() - 2; j++)
                A.addData(std::stod(line[j]), i, j);
            inequality.push_back(i);
            b.addData(std::stod(line[line.size() - 1]), i++);
        }
        else if (line[line.size() - 2] == "==") {
            for (int j = 0; j < line.size() - 2; j++)
                A.addData(std::stod(line[j]), i, j);
            b.addData(std::stod(line[line.size() - 1]), i++);
        }
    }


    vector_t f{ (int)F.size() };
    for (int i = 0; i < F.size(); i++)
        f.addData(F[i], i);

    return { { A,b,f } , conditions , inequality };
}

task_t TaskLoader::makeCanon(task_t M, std::vector<int> conditions, std::vector<int> inequality) {
    Matrix A(M.A.rows, 3 * M.A.cols /*+ inequality.size() - conditions.size()*/);
    std::copy(M.A.begin(), M.A.end(), A.begin());
    vector_t F = M.F;
    vector_t b = M.b;

    int NumberOfLastCoef = M.A.cols;

    //where a <= b => a + x = b
    for (int i : inequality) {
        A(i, NumberOfLastCoef++) = 1;
        F.push_back(0);
    }

    // if b_i < 0 =>   .. * (-1)
    for (int i = 0; i < A.rows; i++)
        if (b[i] < 0) {
            for (int j = 0; j < NumberOfLastCoef; j++)
                A(i, j) = A(i, j) * (-1);
            b[i] = b[i] * (-1);
        }

    //x_i = x_i' - x_lastCoef
    std::vector<int> dop;
    for (int i = 0; i < M.A.cols; i++) {
        if (std::find(conditions.begin(), conditions.end(), i) == conditions.end())
            dop.push_back(1);
        else
            dop.push_back(0);
    }
    int size = M.A.cols;
    for (int j = 0; j < size; j++) {
        if (dop[j] == 1) {
            dop.insert(dop.begin() + j, 0);
            j++;
            size++;
            for (int i = 0; i < M.A.rows; i++) {
                for (int k = A.cols - 1; k > j; k--) {
                    A.addData(A.el(i, k - 1), i, k);
                }
                A.addData(-A.el(i, j - 1), i, j);
            }
            F.insertEl(j, -F[j - 1]);
            NumberOfLastCoef++;

        }
    }
    //delete zero column
   
    for (int j = 0; j < NumberOfLastCoef; j++) {
        int flag = 0;
        for (int i = 0; i < A.rows; i++)
            if (A.el(i, j) == 0)
                flag += 1;

        if (F.el(j, 0) == 0)
            flag += 1;

        if (flag == A.rows + 1) {
            A.deleteEl(j);;
            F.deleteEl(j);
            NumberOfLastCoef--;
            j--;
        }
    }
    A.cols = NumberOfLastCoef;

    return { A, b,F };
}

task_t TaskLoader::makeDual(task_t M, std::vector<int> conditions, std::vector<int> inequality) {
    Matrix A(M.A.T());
    vector_t b = M.F;
    vector_t F = M.b;


    //because x_i >=0 and A^Ty >= F_i => make A^Ty <= F_i 
    for (int i : conditions) {
        for (int j = 0; j < A.cols; j++)
            A(i, j) = A(i, j) * (-1);
        b[i] = b[i] * (-1);
    }

    return makeCanon({ A,b,F }, inequality, conditions);
}

void TaskLoader::printTask(task_t M) {
    std::cout << std::endl;
    for (int i = 0; i < M.A.rows; i++) {
        for (int j = 0; j < M.A.cols; j++) {
            std::cout << std::setw(2) << M.A.el(i, j) << " ";
        }
        std::cout << "= ";
        std::cout << std::setw(2) << M.b.el(i, 0) << std::endl;
    }
    for (int i = 0; i < M.A.cols; i++) {
        std::cout << std::setw(2) << M.F.el(i, 0) << " ";
    }
    std::cout << std::endl;

}