#include "../include/matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 3, "A");

    //filling matrix with random values
    A.fill_random_int(1, 100);

    A.print();
    //finding the inverse of the matrix
    A.inverse().print();
    Matrix::inverse(A).print();

    return 0;
}