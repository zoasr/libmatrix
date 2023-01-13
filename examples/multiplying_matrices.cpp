#include "../include/matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 2);
    Matrix B(2, 4);

    //filling two matrices with random values
    A.fill_random_int(1, 100);
    B.fill_random_int(1, 100);
    A.print();
    B.print();

    //multiplying two matrices together
    (A * B).print();
    A.mult(B).print();
    Matrix::mult(A, B).print();

    return 0;
}