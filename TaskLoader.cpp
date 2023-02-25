#include "TaskLoader.h"
#include<iomanip>

void TaskLoader::load(std::string filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::vector<std::string>> linearSystem;
    std::vector<int> conditions;
    std::vector<double> F;

    //read data from the file
    int inequalities = 0;
    int equalities = 0;
    bool nextIter = false;
    int state = 0;
    while (std::getline(file, line)) {
        std::vector<std::string> result;
        std::istringstream iss(line);

        for (std::string s; iss >> s; )
            result.push_back(s);

        if (state == 0) {
            for (int i = 0; i < result.size(); i++)
                if (result[i] == ">=" || result[i] == "<=" || result[i] == "==") {
                    if (result[i] == "==")
                        equalities++;
                    else
                        inequalities++;
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

    int N = F.size() * 3;

    Matrix A1{ inequalities, N }, A2{ equalities, N };
    vector_t b1{ inequalities }, b2{ equalities };

    int A1Index = 0, A2Index = 0;
    for (auto& line : linearSystem) {
        if (line[line.size() - 2] == ">=") {
            // we must change sign, so multiply everything by -1
            for (int i = 0; i < line.size() - 2; i++) {
                A1.addData(std::stod(line[i]) * (-1), A1Index, i);
                std::cout << A1.el(A1Index, i) << " ";
            }
            std::cout << "<= ";
            b1.addData((-1) * std::stod(line[line.size() - 1]), A1Index++);
            std::cout << b1.el(A1Index - 1, 0) << std::endl;
        }
        if (line[line.size() - 2] == "<=") {
            for (int i = 0; i < line.size() - 2; i++) {
                A1.addData(std::stod(line[i]), A1Index, i);
                std::cout << A1.el(A1Index, i) << " ";
            }
            std::cout << "<= ";
            b1.addData(std::stod(line[line.size() - 1]), A1Index++);
            std::cout << b1.el(A1Index - 1, 0) << std::endl;
        }
        if (line[line.size() - 2] == "==") {
            for (int i = 0; i < line.size() - 2; i++) {
                A2.addData(std::stod(line[i]), A2Index, i);
                std::cout << A2.el(A2Index, i) << " ";
            }
            std::cout << "== ";
            b2.addData(std::stod(line[line.size() - 1]), A2Index++);
            std::cout << b2.el(A2Index - 1, 0) << std::endl;
        }
    }

    int NumberOfLastCoef = F.size();

    //add coef where x>=0 => x = x' - x"
    std::vector<int> dop;
    for (int i = 0; i < F.size(); i++) {
        if (std::find(conditions.begin(), conditions.end(), i) == conditions.end())
            dop.push_back(1);
        else
            dop.push_back(0);
    }
    for (int j = 0; j < F.size(); j++) {
        if (dop[j] == 1) {
            for (int i = 0; i < inequalities; i++)
                A1.addData(A1.el(i, j), i, NumberOfLastCoef);
            for (int i = 0; i < equalities; i++)
                A2.addData(A2.el(i, j), i, NumberOfLastCoef);
            NumberOfLastCoef++;

            for (int i = 0; i < inequalities; i++)
                A1.addData(-A1.el(i, j), i, NumberOfLastCoef);
            for (int i = 0; i < equalities; i++)
                A2.addData(-A2.el(i, j), i, NumberOfLastCoef);
            NumberOfLastCoef++;

            for (int i = 0; i < inequalities; i++)
                A1.addData(0, i, j);
            for (int i = 0; i < equalities; i++)
                A2.addData(0, i, j);
        }
    }

    //remove the extra columns, where all zeros
    for (int j = 0; j < NumberOfLastCoef; j++) {
        int flag = 0;
        for (int i = 0; i < inequalities; i++)
            if (A1.el(i, j) == 0)
                flag += 1;

        for (int i = 0; i < equalities; i++)
            if (A2.el(i, j) == 0)
                flag += 1;

        if (flag == inequalities + equalities) {
            A1.deleteEl(j);
            A2.deleteEl(j);
            NumberOfLastCoef--;
            j--;
        }
    }
    // from <= to =
    for (int i = 0; i < inequalities; i++) {
        A1.addData(1, i, NumberOfLastCoef);
        NumberOfLastCoef++;
    }

    // if b[i]< 0 do that b[i] > 0 
    {

        for (int i = 0; i < inequalities; i++) {
            if (b1.el(i, 0) < 0) {
                for (int j = 0; j < NumberOfLastCoef; j++) {
                    A1.addData(A1.el(i, j) * (-1), i, j);
                }
                b1.addData((-1) * b1.el(i, 0), i);
            }
        }
        for (int i = 0; i < equalities; i++) {
            if (b2.el(i, 0) < 0) {
                for (int j = 0; j < NumberOfLastCoef; j++) {
                    A2.addData(A2.el(i, j) * (-1), i, j);
                }
                b2.addData((-1) * b2.el(i, 0), i);
            }
        }
    }

    std::cout << std::endl;
    for (int i = 0; i < inequalities; i++) {
        for (int j = 0; j < NumberOfLastCoef; j++) {
            std::cout << std::setw(2) << A1.el(i, j) << " ";
        }
        std::cout << "= ";
        std::cout << std::setw(2) << b1.el(i, 0) << std::endl;
    }
    for (int i = 0; i < equalities; i++) {
        for (int j = 0; j < NumberOfLastCoef; j++) {
            std::cout << std::setw(2) << A2.el(i, j) << " ";
        }
        std::cout << "= ";
        std::cout << std::setw(2) << b2.el(i, 0) << std::endl;
    }

}