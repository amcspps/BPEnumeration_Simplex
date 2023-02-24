#ifndef VECTOR_H_
#define VECTOR_H_
#include "matrix_t.h"

struct vector_t : public matrix_t {
    vector_t(int h) : matrix_t(h, 1) {};
    vector_t(matrix_t& mat) : matrix_t(mat) {
        rows *= cols;
        cols = 1;
    };
    inline double& operator[](const int i) { return el(i, 0); }
    inline double operator[](const int i) const { return el(i, 0); }
    void push_back(double el) {
        _data.push_back(el);
        rows++;
    }
    double eqNorm() const;
};
double norm(const vector_t& v);
#endif // VECTOR_H_