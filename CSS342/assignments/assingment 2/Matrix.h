#pragma once
#include "Vector.h"
#include <string>
class Matrix{
    private:
        int rows;
        int cols;
        int** matrix;
    public:
        friend class Vector;   
        Matrix();
        Matrix(int r, int c);
        ~Matrix();
        int getRows();
        int getColumns();
        int getData(int x, int y);
        void setData(int x, int y, int data);
        float l2Normal();
        Matrix operator*(Matrix b);
        Vector operator*(Vector b);
        int trace();
        Matrix transpose();
};

//to call, matrix[x][y] = *(matrix + (rows*x) +y)