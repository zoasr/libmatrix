#include "../include/matrix.h"
using namespace std;

int main()
{
	double theta = 3.14 / 4;
	Matrix::rotation(theta).print();
	Matrix::rotationX(theta).print();
	Matrix::rotationY(theta).print();
	Matrix::rotationZ(theta).print();
	return 0;

	/**
Matrix ( R(theta) )[2x2] is:

┌        0.707  -0.707   ┐
└        0.707  0.707    ┘



Matrix ( R(theta, i) )[3x3] is:

┌        1.000  0.000   0.000    ┐
|        0.000  0.707   -0.707   |
└        0.000  0.707   0.707    ┘



Matrix ( R(theta, j) )[3x3] is:

┌        0.707  0.000   0.707    ┐
|        0.000  1.000   0.000    |
└        -0.707 0.000   0.707    ┘



Matrix ( R(theta, k) )[3x3] is:

┌        0.707  -0.707  0.000    ┐
|        0.707  0.707   0.000    |
└        0.000  0.000   1.000    ┘
	*/
}