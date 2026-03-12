#include <cmath>
#include "Matrix.h"
Matrix::Matrix(){
    rows = 3;
    cols = 3;
    matrix = new int*[rows];
    for(int i = 0; i < rows; i++){
        matrix[i] = new int[cols];
    }
} //matrix of size 3x3;

Matrix::Matrix(int r, int c){
    rows = r;
    cols = c;
    matrix = new int*[rows];
    for(int i = 0; i < rows; i++){
        matrix[i] = new int[cols];
    }
}
Matrix::~Matrix(){
    for(int i = 0; i < rows; i++){
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
}
int Matrix::getColumns(){
    return cols;
}
int Matrix::getRows(){
    return rows;
}
int Matrix::getData(int x, int y){
    return matrix[x][y];
}
void Matrix::setData(int x, int y, int data){
    matrix[x][y] = data;
} 

//square root of the sums of the absolute elements
float Matrix::l2Normal(){
    float total = 0.0f;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            total += pow(matrix[i][j], 2);
        }
    }
    return sqrt(total);
}
Matrix Matrix::operator*(Matrix b){
    //for matrix mult, the number of columns in the first matrix must be equal to the number of rows in the second matrix
    if(rows != b.getColumns()){
        Matrix c = Matrix();
        return c;
    }
    //makes a new matrix object
    Matrix c = Matrix(rows , b.getColumns());
    //for each of their row, take the dot product, axbx + ayby + azbz
    //uses kstop to ensure it doesnt go out of bounds
    int kstop;
    if(cols > b.getRows()) kstop = b.getRows();
    else kstop = cols;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < b.getColumns(); j++){
            int m = 0;
            for(int k = 0; k < kstop; k++){
                //c[i][j] += matrix[i][k] * b.matrix[k][j];
                //sets the data at i,j with 
                m += matrix[i][k] * b.getData(k,j);
            }
            c.setData(i,j, m);
        }
    }
    return c;
}

Vector Matrix::operator*(Vector b){
    if(rows != b.getCapacity()){
        Vector c = Vector();
        return c;
    }
    Vector c = Vector(b.getCapacity());
    for(int i = 0; i < rows; i++){
        int m = 0;
        for(int j = 0; j < cols; j++){
            m += matrix[i][j] * b.getDataAt(i);
        }
        c.setDataAt(i, m);
    }
    return c;
}

int Matrix::trace(){
    if(rows == cols){
        int m = 0;
        for(int i = 0; i < rows; i++){
            m += matrix[i][i];
        }
        return m;
    }else return -1;
}
Matrix Matrix::transpose(){
    Matrix c =Matrix(cols, rows);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            c.setData(j,i, matrix[i][j]);
        }
    }
    return c;
}