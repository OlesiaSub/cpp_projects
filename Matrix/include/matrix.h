#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <exception>

class Matrix {
public:
    Matrix(int rows_, int cols_);
    Matrix(const Matrix& other);

    inline int get_rows() {
        return rows;
    }
    inline int get_cols() {
        return cols;
    }

    int get_data(int row, int col) const;

	void load_matrix();

	Matrix& operator=(const Matrix& other);
    Matrix operator+(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix& operator*=(const Matrix& other);

private:
    int rows;
	int cols;
    std::vector<std::vector<int>> data;
};

class MatrixException : public std::exception {
public:
    MatrixException(const char* message = "None") : message(message) {};
    inline const char* get() const {
		return message;
	}
private:
    const char* message;
};
