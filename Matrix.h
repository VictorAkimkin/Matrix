#pragma once
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
class Matrix
{
public:
	//constructors
	Matrix();
	Matrix(size_t _row, size_t _columns);
	//copy constructor
	Matrix(const Matrix &other);
	//move constructor
	Matrix(Matrix &&other)noexcept;

	// destructor
	~Matrix();
public:
	//ostream operator<<
	friend std::ostream& operator<< (std::ostream& out, const Matrix& _matrix);
	// operators
	bool operator==(const Matrix& other);
	bool operator!=(const Matrix& other);
	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix operator*(const double number);
	Matrix operator/(const double number);
	double *operator[] (const size_t _row)const;
public:
	// public methods
	void RebuildMatrix(size_t _row, size_t _columns);// delete old data and build matrix with new params
	bool IsMayAddOrSubstract(const Matrix& other);// may the matrix be added or subtracted 
	bool IsMayMultiplied(const Matrix& other);// may the matrix be multiplied or divided
	void Transposition();// matrix transposition
	Matrix HadamardProduct(const Matrix& other);// returns a matrix of multiplied corresponding elements of the existing matrix and the incoming one
	void ZeroFillMatrix();// fill the matrix with zeros
	void RndFillMatrix(int min, int max);// fill the matrix with random vaulues
private:
	// private methods
	double** CreateMatrix(size_t _rows, size_t _columns);// create a matrix
	void InitMatrix();// initilize current matrix
	void DeleteMatrix();// delete current matrix
private:
	//variables
	size_t Columns{}, Rows{};
	double **Data=nullptr;
};

