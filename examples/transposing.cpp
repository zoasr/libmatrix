#include "..\src\matrix.h"
#include "iostream"
using namespace std;

int main()
{
    Matrix A(3, 3, "A");

    //filling matrix with random values
    A.fill_random_int(1, 100);

    A.print();
    //transposing the matrix
    A.transpose().print();
    Matrix::transpose(A).print();

    return 0;
}