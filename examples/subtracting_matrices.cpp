#include "..\include\matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 3);
    Matrix B(3, 3);

    //filling two matrices with random values
    A.fill_random_int(1, 100);
    B.fill_random_int(1, 100);

    //subtracting two matrices together
    (A - B).print();
    A.sub(B).print();
    Matrix::sub(A, B).print();

    return 0;
}