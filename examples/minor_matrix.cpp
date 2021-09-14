#include "..\src\matrix.h"
using namespace std;

int main()
{

    Matrix A(3, 3, "A");

    // filling matrix with random values
    A.fill_random_int(1, 100);

    A.print();

    /**
    * extracting a minor matrix from matrix "A" at position[1, 2](1st row, 2nd column)
    */
    A.minor(1, 2).print();
    Matrix::minor(A, 1, 2).print();

    return 0;
}

