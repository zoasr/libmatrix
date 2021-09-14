#include "..\include\matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 3, "A");
    Matrix B(3, 3, "B");

    //filling two matrices with random values
    A.fill_random_int(1, 100);
    B.fill_random_int(1, 100);

    //adding two matrices together
    (A + B).print();
    A.add(B).print();
    Matrix::add(A, B).print();

    return 0;
}