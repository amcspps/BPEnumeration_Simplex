#ifndef VECTOR_H_
#define VECTOR_H_
#pragma once
#include "matrix_t.h"

struct vector_t : public Matrix {
    vector_t(int h) : Matrix(h, 1) {};
    vector_t(Matrix& mat) : Matrix(mat) {
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

    inline void addData(int data, int i) { Matrix::addData(data, i, 0); };
    void deleteEl(int _j);
    void insertEl(int _j, int data) { _data.insert(_data.begin() + _j, data); };
};
double norm(const vector_t& v);
#endif // VECTOR_H_