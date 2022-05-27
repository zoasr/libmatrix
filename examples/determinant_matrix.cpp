#include "..\include\matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 3, "A");

    //filling matrix with random values
    A.fill_random_int(1, 5);

    A.print();
    //finding the determinant of the matrix
    cout << A.determ() << endl;
    cout << Matrix::determ(A);

    return 0;
}