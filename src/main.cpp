#include "../include/matrix.h"
#include <iostream>
// using namespace std;

int main()
{

	Matrix A(3, 3, 5);
	Matrix I = Matrix::IDENTITY(3);
	// Matrix B(3, 3, 2);
	// A.data = { {0, 1, -3}, { 5, 0, -7}, {4, -1, 0} };
	// A.add(B).print();
	// Matrix::add(A, B).print();
	// Matrix::add(Matrix(1, 1, 10), A).print();
	// A.print();
	A.mult(I).print();
	// A.minor(5, 30);
	// A.input();
	// A.fill_random_int(5, 10);
	// std::cout << A.determ() << std::endl;

	// A.appendUp(I).inverse().print();
	// A.print();
	// A.rotate(-1).print();

	// A.print();
	// A.inverse().print();
	// B.print();

	// //multiplying two matrices together
	// (A * B).print();

	// A.mult(B).print();
	// Matrix::mult(A, B).print();
	return 0;
}