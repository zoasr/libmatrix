#include "../include/matrix.h"
using namespace std;

int main()
{
	Matrix A(3, 3, "A");
	double trace = 0;
	A.fill_random_int(1, 100);
	A.print();
	trace = A.trace();
	printf("Trace of Matrix (A) = %f\n", trace);
	trace = Matrix::trace(A);
	printf("Trace of Matrix (A) = %f\n", trace);
	return 0;
}