#include "..\src\matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 3, "A");

    //filling matrix with random values
    A.fill_random_int(1, 100);

    A.print();
    //finding a certain power multiplication with a certain exponent (2) of the matrix
    A.power(3).print();
    Matrix::power(A, 3).print();
    (A ^ 3).print();

    return 0;
}