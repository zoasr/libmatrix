#pragma once
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "consoleColor.h"
#include "Vector2D.h"


#define UR_BRACKET	"┐"
#define BL_BRACKET	"└"
#define BR_BRACKET	"┘"
#define UL_BRACKET	"┌"


#ifndef MCLASS_H
#define MCLASS_H

class Matrix {
private:
	double m_init = 0;
	std::string original_name = "UNNAMED";
public:
	std::vector<std::vector<double>> data = { {0} };
	int m_rows = 1;
	int m_cols = 1;
	std::string name = "UNNAMED";

	Matrix(void) {};
	~Matrix() {};


	Matrix(size_t y, size_t x, double m_init = 0) {
		if (y <= 0 || x <= 0) {
			this->m_rows = 1;
			this->m_cols = 1;
			sprintf(buffer, "%g", m_init);
			this->name = buffer;
			this->original_name = buffer;
			this->data.assign(1, std::vector<double>(1, m_init));
		}
		else if (x == 1 && y == 1 || (x < 1 || y < 1)) {
			this->m_rows = y;
			this->m_cols = x;
			sprintf((char*)buffer, "%g", m_init);
			this->name = buffer;
			this->original_name = buffer;
			this->data.assign(1, std::vector<double>(1, m_init));
		}
		else {
			this->data.assign(y, std::vector<double>(x, m_init));
			this->m_rows = y;
			this->m_cols = x;
			this->name = "UNNAMED";
			this->original_name = "UNNAMED";
		}
	}
	Matrix(size_t y, size_t x, std::string n, double m_init = 0) {
		if (y <= 0 || x <= 0) {
			this->m_rows = 1;
			this->m_cols = 1;
			this->name = n;
			this->original_name = n;
			this->data.assign(1, std::vector<double>(1, m_init));
		}
		else if (x == 1 && y == 1 || (x < 1 || y < 1)) {
			this->m_rows = y;
			this->m_cols = x;
			this->name = n;
			this->original_name = n;
			this->data.assign(1, std::vector<double>(1, m_init));
			return;
		}
		else {
			this->data.assign(y, std::vector<double>(x, m_init));
			this->m_rows = y;
			this->m_cols = x;
			this->name = n;
			this->original_name = n;
		}
	}
	Matrix(std::string n) { this->name = n; }

	static Matrix IDENTITY(int order, bool n = true);


	/**
	* @brief adding this matrix to another matrix
	* , the two matrices must be of the same size
	* @param a matrix being added
	* @returns Matrix with same size
	*/
	Matrix add(Matrix a);

	/**
	 * @brief adding two matrices to each other
	 * , the two matrices must be of the same size
	 * @param a first matrix
	 * @param b second matrix
	 * @returns Matrix of the same size
	 */
	static Matrix add(Matrix a, Matrix b) {
		return a.add(b);
	}

	Matrix operator+(const Matrix& rhs) {
		return this->add(rhs);
	}

	/**
	 * @brief Gives the augmented matrix :  A|B,
	 * has the operator |
	 * @param a Matrix being appended
	 * @returns Augmented matrix with the columns = A.rows x (A.columns + B.columns)
	 */
	Matrix augment(Matrix a);
	/**
	 * @brief Gives the augmented matrix :  A|B
	 * has the operator |
	 * @param a Matrix to append to.
	 * @param b Matrix being appended.
	 * @returns Augmented matrix with the columns = A.rows x (A.columns + B.columns)
	 */
	static Matrix augment(Matrix a, Matrix b) { return a.augment(b); }
	Matrix operator|(const Matrix& rhs) { return this->augment(rhs); }

	/**
	 * @brief Appends a given matrix above this matrix (same as augmeting the matrix but on adifferent axis)
	 * @param a Matrix being appended
	 * @returns Matrix with the columns = A.rows x (B.columns + A.columns)
	 */
	Matrix appendUp(Matrix a);

	/**
	 * @brief Appends a given matrix below this matrix (same as augmeting the matrix but on adifferent axis)
	 * @param a Matrix being appended
	 * @returns Matrix with the columns = (A.rows + B.rows) x A.columns
	 */
	Matrix appendDown(Matrix a);

	/**
	 * @brief subtracting a matrix from this matrix
	 * , the two matrices must be of the same size
	 * @param a matrix to sbtract
	 * @returns Matrix of the same size
	 */
	Matrix sub(Matrix a);

	/**
	 * @brief subtracting two matrices from each other
	 * , the two matrices must be of the same size
	 * @param a first matrix
	 * @param b second matrix
	 * @returns Matrix of the same size
	 */
	static Matrix sub(Matrix a, Matrix b) {
		return a - b;
	}

	Matrix operator-(const Matrix& rhs) {
		return this->sub(rhs);
	}

	/**
	 * @brief Multiplying two matrices (every row * every column).
	 *
	 * NOTE: number of this matrix's columns must equal the other matrix's number
	 * of rows
	 * multiplying first row of this matrix with columns (1, 2, 3, ...) of a
	 * multiplying second row of this matrix with columns (1, 2, 3, ...) of a
	 * .
	 * .
	 * .
	 * .
	 * @param a the matrix you want muliply by
	 * @returns A matrix with this matrix rows and a's columns
	 */
	Matrix mult(Matrix a);

	Matrix mult(double a);

	/**
	 * @brief Multiplying two matrices (every row * every column)
	 * NOTE: number of a's columns must equal  b's number of rows
	 * multiplying first row of a with columns (1, 2, 3, ...) of b
	 * multiplying second row with columns (1, 2, 3, ...) of b
	 * .
	 * .
	 * @param a the matrix
	 * @param b the matrix you want muliply by
	 * @returns A matrix with a's rows and b's columns
	 */
	static Matrix mult(Matrix a, Matrix b) {
		return a.mult(b);
	}
	static Matrix mult(double a, Matrix b) {
		return b.mult(a);
	}
	static Matrix mult(Matrix a, double b) {
		return a.mult(b);
	}

	Matrix operator*(const Matrix& rhs) {
		return this->mult(rhs);
	}

	/**
	 *   @brief transpose a given matrix (switching every column with every row and
	 * vice versa)
	 *   @return a transposed matrix
	 */
	Matrix transpose();

	/**
	 *   @brief transpose a give matrix (switching every column with every row and
	 * vice versa)
	 *   @return a transposed matrix
	 *   @param a matrix to transpose
	 */
	static Matrix transpose(Matrix a) {
		return a.transpose();
	}

	/**
	 *   @brief rotates a given matrix by 90 degrees (clockwise or anticlockwise)
	 * depending on the direction
	 *   @return a rotated matrix
	 *   @param dir  rotation direction :-ve: Clockwise , +ve: anticlockwise the value
	 *   of the direction determines how many times the matrix will be rotated
	 */
	Matrix rotate(int dir);

	/**
	 *   @brief rotates a given matrix by 90 degrees (clockwise or anticlockwise)
	 * depending on the direction
	 *   @return a rotated matrix
	 *   @param a matrix to rotate
	 *   @param dir  rotation direction :-ve: Clockwise , +ve: anticlockwise the value\n
	 *   of the direction determines how many times the matrix will be rotated
	 */
	static Matrix rotate(Matrix a, int dir) {
		return a.rotate(dir);
	}
	/**
	 *   @brief find a minor matrix at a given row and column.
	 *   it uses a brute force algorithm to find the minor matrix at any given
	 * element of the matrix
	 *   @param i_ row
	 *   @param j_ column
	 *   @return a Matrix with rows - 1 and columns - 1
	 */
	Matrix minor(int i_, int j_);

	/**
	 *   @brief find a minor matrix at a given row and column.
	 *   it uses a brute force algorithm to find the minor matrix at any given
	 * element of the matrix
	 *   @param i_ row
	 *   @param j_ column
	 *   @return a Matrix with rows - 1 and columns - 1
	 */
	static Matrix minor(Matrix a, int i_, int j_) {
		return a.minor(i_, j_);
	}

	/**
	 * @brief Calculates inverse using the adjoint
	 * takes only a square Matrix (N*N)
	 * @returns Matrix with same size
	 */
	Matrix inverse();


	/**
	 * @brief Calculates inverse using the adjoint
	 * takes only a square Matrix (N*N)
	 * @param a Matrix to calculate the inverse of
	 * @returns Matrix with same size
	 */
	static Matrix inverse(Matrix a) {
		return a.inverse();
	}

	/**
	 * @brief Calculate the determinant of a given matrix
	 * this function uses recursion by minimizing the given matrix to 2*2 matrices
	 * to calculate the determinant.
	 * it takes only square matrices (N*N)
	 * @returns Scalar value
	 */
	double determ();


	/**
	 * @brief Calculate the determinant of a given matrix
	 * this function uses recursion by minimizing the given matrix to 2*2 matrices
	 * to calculate the determinant.
	 * it takes only square matrices (N*N)
	 * @param a Matrix
	 * @param n number of rows or columns of the matrix
	 * @returns Scalar value
	 */
	static double determ(Matrix a) {
		return a.determ();
	}

	/**
	 * @brief Calculate the power of a given matrix
	 * Multiplies the same matrix to itself a given number of times
	 * it takes only square matrices (N*N)
	 * @param n exponent
	 * @returns Matrix
	 */
	Matrix power(int n);
	/**
	 * @brief Calculate the power of a given matrix
	 * Multiplies the same matrix to itself a given number of times
	 * it takes only square matrices (N*N)
	 * @param a matrix
	 * @param n exponent
	 * @returns Matrix
	 */
	static Matrix power(Matrix a, int n) {
		return a.power(n);
	}

	Matrix operator^(const int& n) {
		return this->power(n);
	}


	/**
	 * prints the given matrix on the console screen
	 */
	void print();
	/**
	 * prints the given matrix on the console screen
	 * @param a Matrix
	 */
	static void print(Matrix a) {
		a.print();
	}

	/**
	 * takes the matrix values from the user
	 */
	void input();

	/**
	 * takes the matrix values from the user
	 * @param a Matrix
	 */
	static void input(Matrix a) {
		a.input();
	}


	/**
	 * fills the matrix cells with random double values in a certain range
	 * @param a lowest value possible
	 * @param b highest value possible
	 */
	void fill_random(int a, int b);

	/**
	 * fills the matrix cells with random double values in a certain range
	 * @param m matrix
	 * @param a lowest value possible
	 * @param b highest value possible
	 */
	static void fill_random(Matrix m, int a, int b) {
		m.fill_random(a, b);
	}
	/**
	 * fills the matrix cells with random integer values in a certain range
	 * @param a lowest value possible
	 * @param b highest value possible
	 */
	void fill_random_int(int a, int b);

	/**
	 * fills the matrix cells with random integer values in a certain range
	 * @param m matrix
	 * @param a lowest value possible
	 * @param b highest value possible
	 */
	static void fill_random_int(Matrix m, int a, int b) {
		m.fill_random_int(a, b);
	}

private:

	char buffer[50];

	static double randomDouble(double a, double b);
};

#endif
