#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#include "matrix.h"

Matrix::Matrix(int rows_, int cols_) : rows(rows_), cols(cols_) {
    data = std::vector<std::vector<int>> (rows);
    for (int i = 0; i < rows; ++i) {
        data[i] = std::vector <int> (cols);
        for (int j = 0; j < cols; j++) {
            data[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& other) : Matrix(other.rows, other.cols) {
    for (int i = 0; i < other.rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            data[i][j] = other.get_data(i, j);
        }
    }
}

int Matrix::get_data(int row, int col) const {
    if (col >= cols || row >= rows || col < 0 || row < 0) {
        throw MatrixException("ACCESS: bad index.");
    }
    return data[row][col];
}

void Matrix::load_matrix() {
	std::string name;
	std::cin >> name;
	std::fstream file(name);
    int rows, cols, value;
	if (!file.is_open()) {
		throw MatrixException("LOAD: unable to open file.");
	}
    if (!(file >> rows) || !(file >> cols)) {
		throw MatrixException("LOAD: invalid file format.");
	}
	Matrix m(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(file >> value)) {
				throw MatrixException("LOAD: invalid file format.");
			} else {
                m.data[i][j] = value;
            }
        }
	}
	*this = m;
	return;
}

Matrix& Matrix::operator=(const Matrix& other) {
	Matrix copy = Matrix(other);
	std::swap(this->rows, copy.rows);
	std::swap(this->cols, copy.cols);
	std::swap(this->data, copy.data);
	return *this;
}

Matrix Matrix::operator+(const Matrix& other) {
    if (this->cols != other.cols || this->rows != other.rows) {
        throw MatrixException("ADD: dimensions do not match.");
    }
    Matrix sum(rows, cols);
    for (int h = 0; h < rows; h++) {
        for (int w = 0; w < cols; w++) {
            sum.data[h][w] = this->get_data(h, w) + other.get_data(h, w);
        }
    }
    return sum;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    return *this = *this + other;
}

Matrix Matrix::operator*(const Matrix& other) {
    if (this->cols != other.rows) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
    Matrix mul(this->rows, other.cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < other.cols; j++) {
			mul.data[i][j] = 0;
            for (int k = 0; k < this->cols; k++) {
                mul.data[i][j] += this->get_data(i, k) * other.get_data(k, j);
            }
        }
    }
    return mul;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    return *this = *this * other;
}
