#include "..\include\matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 3, "A");

    //filling matrix with random values
    A.fill_random_int(1, 100);

    A.print();
    //rotating the matrix clockwise
    A.rotate(-1).print();
    Matrix::rotate(A, -4).print();

    // //rotating the matrix anti-clockwise
    // A.rotate(-2).print();
    // Matrix::rotate(A, 2).print();

    return 0;
}