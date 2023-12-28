#pragma once
#include "Matrix.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>

void func(Matrix && matrix)
{
	std::cout << matrix;
	std::cout << "\n";
}
void func(Matrix& matrix)
{
	std::cout << matrix;
	std::cout << "\n";
}

void main()
{
	int row=2, col = 3;
	Matrix matrix(row, col);
	matrix.RndFillMatrix(-100,200);
	matrix[0][0] = 5;
	matrix[1][2] = 5;
	
	Matrix matrix1(row, col);
	matrix1[0][0] = 1; matrix1[0][1] = 2; matrix1[0][2] = 3;
	matrix1[1][0] = 4; matrix1[1][1] = 5; matrix1[1][2] = 6;

	Matrix matrix2(row, col);
	matrix2[0][0] = 10; matrix2[0][1] = 20; matrix2[0][2] = 30;
	matrix2[1][0] = 40; matrix2[1][1] = 50; matrix2[1][2] = 60;


	setlocale(0, "Ru");
	std::cout << "Матрица:\n";
	std::cout << matrix;
	std::cout << "\n";

	std::cout << matrix1;
	std::cout << "\n";
	std::cout << matrix2;
	std::cout << "\n";
	std::cout << (matrix1 + matrix2);
	std::cout << "\n";

	matrix2.Transposition();
	std::cout << matrix2;
	std::cout << "\n";
	std::cout << (matrix1 * matrix2);
	std::cout << "\n";

	matrix2.Transposition();
	std::cout << matrix1.HadamardProduct(matrix2);
	std::cout << "\n";
	
	func(std::move(matrix2));
	func(matrix2);

	system("pause");
}