#include "..\src\matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 2, 584812.32545);
    Matrix B(2, 4, 5154.051);

    //filling two matrices with random values
    A.print();
    B.print();

    //multiplying two matrices together
    (A * B).print();
    A.mult(B).print();
    Matrix::mult(A, B).print();

    return 0;
}