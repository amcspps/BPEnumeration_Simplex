#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "matrix_t.h"
#include "vector_t.h"

class TaskLoader {
public:
	void load(std::string filename) {
        std::ifstream file(filename);
        std::string line;
        std::vector<std::vector<std::string>> linearSystem;
        std::vector<int> conditions;
        std::vector<double> c;


        //read data from the file
        int inequalities = 0;
        int equalities = 0;
        bool nextIter = false;
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
                    c.push_back(std::stod(result[i]));
            }
            state++;
        }

        // now lets fix everything and remember what we fixed/ 
        // FIRST - all elements must be in matrix and vectors
        vector_t c_to_build(c.size());
        Matrix A1(inequalities, c.size()), A2(equalities, c.size());
        vector_t b1(inequalities), b2(equalities);


	}
};