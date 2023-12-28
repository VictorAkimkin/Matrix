#include "Matrix.h"
//constructors
Matrix::Matrix()
{}
Matrix::Matrix(size_t _row, size_t _columns) :Columns(_columns), Rows(_row)
{
	if (!Columns || !Rows)
		return;
	InitMatrix();
	ZeroFillMatrix();
}
//copy constructor
Matrix::Matrix(const Matrix& other)
{
	DeleteMatrix();
	Rows = other.Rows;
	Columns = other.Columns;
	InitMatrix();
	for (size_t i = 0; i < Rows; ++i)
		for (size_t j = 0; j < Columns; ++j)
		{
			Data[i][j] = other.Data[i][j];
		}
}
//move constructor
Matrix::Matrix(Matrix&& other) noexcept
{
	DeleteMatrix();
	Rows = other.Rows;
	Columns = other.Columns;
	Data = other.Data;
	other.Data = nullptr;
}
// destructor
Matrix::~Matrix()
{
	DeleteMatrix();
}
//methods
// create a matrix
double** Matrix::CreateMatrix(size_t _rows, size_t _columns)
{
	double **NewData = new double* [_rows];
	for (size_t i=0;i< _rows;++i)
		NewData[i] = new double[_columns];
	return NewData;
}
// initilize current matrix
void Matrix::InitMatrix()
{
	Data = CreateMatrix(Rows,Columns);
}
// delete the matrix
void Matrix::DeleteMatrix()
{
	if (Data == nullptr)
		return;
	for (size_t i = 0; i < Rows; ++i)
		delete[] Data[i];
	delete[] Data;
}
// fill the matrix with zeros
void Matrix::ZeroFillMatrix()
{
	for (size_t i = 0; i < Rows; ++i)
		std::memset(Data[i], 0, sizeof(double)*Columns);
}
// fill the matrix with random vaulues
void Matrix::RndFillMatrix(int min, int max)
{
	std::srand(std::time(NULL));
	for (size_t i = 0; i < Rows; ++i)
		for (size_t j = 0; j < Columns; ++j)
			Data[i][j] = std::rand()%(max-min) + min;
}
// may the matrix be added or subtracted 
bool Matrix::IsMayAddOrSubstract(const Matrix& other)
{
	return Columns == other.Columns && Rows == other.Rows;
}
// may the matrix be multiplied or divided
bool Matrix::IsMayMultiplied(const Matrix& other)
{
	return Columns == other.Rows;
}
// matrix transposition
void Matrix::Transposition()
{
	double **NewData=CreateMatrix(Columns, Rows);
	for (size_t i = 0; i < Columns; ++i)
		for (size_t j = 0; j < Rows; ++j)
		{
			NewData[i][j] = Data[j][i];
		}
	DeleteMatrix();
	std::swap(Columns, Rows);
	Data = NewData;
}
// returns a matrix of multiplied corresponding elements of the existing matrix and the incoming one
Matrix Matrix::HadamardProduct(const Matrix& other)
{
	if (!IsMayAddOrSubstract(other))
	return Matrix();
	Matrix ResultMatrix(Rows, Columns);
	for (size_t i = 0; i < Rows; ++i)
		for (size_t j = 0; j < Columns; ++j)
			ResultMatrix[i][j] = Data[i][j] * other.Data[i][j];
	return ResultMatrix;
}
// operators
bool Matrix::operator==(const Matrix& other)
{
	if (!IsMayAddOrSubstract(other))
		return false;
	for (size_t i = 0; i < Rows; ++i)
		for (size_t j = 0; j < Columns; ++j)
			if (Data[i][j] != other.Data[i][j])
				return false;
	return true;
}
bool Matrix::operator!=(const Matrix& other)
{
	return !(*this== other);
}
// Matrix+Matrix
Matrix Matrix::operator+(const Matrix& other)
{
	if (!IsMayAddOrSubstract(other))
		return Matrix();
	Matrix ResultMatrix(Rows, Columns);
	for (size_t i = 0; i < Rows; ++i)
		for (size_t j = 0; j < Columns; ++j)
			ResultMatrix[i][j] =Data[i][j] + other.Data[i][j];
	return ResultMatrix;
}
// Matrix-Matrix
Matrix Matrix::operator-(const Matrix& other)
{
	if (!IsMayAddOrSubstract(other))
		return Matrix();
	Matrix ResultMatrix(Rows, Columns);
	for (size_t i = 0; i < Rows; ++i)
		for (size_t j = 0; j < Columns; ++j)
			ResultMatrix[i][j] = Data[i][j] - other.Data[i][j];
	return ResultMatrix;
}
// Matrix*Matrix
Matrix Matrix::operator*(const Matrix& other)
{
	if (!IsMayMultiplied(other))
		return Matrix();
	Matrix ResultMatrix(Rows, other.Columns);
	double tmpSum;
	for (size_t i = 0; i < Rows; ++i)
		for (size_t j = 0; j < other.Columns; ++j)
		{
			tmpSum = 0;
			for (size_t k = 0; k < Columns; ++k)
				tmpSum += Data[i][k] * other.Data[k][j];
			ResultMatrix[i][j] = tmpSum;	
		}
	return ResultMatrix;
}
// Matrix*number
Matrix Matrix::operator*(const double number)
{
	Matrix ResultMatrix(Rows, Columns);
	for (size_t i = 0; i < Rows; ++i)
		for (size_t j = 0; j < Columns; ++j)
			ResultMatrix[i][j] =Data[i][j] * number;
	return ResultMatrix;
}
// Matrix/number
Matrix Matrix::operator/(const double number)
{
	Matrix ResultMatrix(Rows, Columns);
	for (size_t i = 0; i < Rows; ++i)
		for (size_t j = 0; j < Columns; ++j)
			ResultMatrix[i][j] = Data[i][j] / number;
	return ResultMatrix;
}
double* Matrix::operator[] (const size_t _row)const
{
	return Data[_row];
}
//ostream operator<<
std::ostream& operator<< (std::ostream& out, const Matrix& _matrix)
{
	for (size_t i = 0; i < _matrix.Rows; ++i)
	{
		for (size_t j = 0; j < _matrix.Columns; ++j)
			out << _matrix[i][j] << "  ";
		out << "\n";
	}
	return out;
}
