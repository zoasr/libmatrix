#include "../include/matrix.h"
using namespace std;

int main()
{
    //initializing a 3*3 matrix with the name "A"
    Matrix A(3, 3, "A");

    //accesing the data vectors to input matrix data
    A.data = { {1, 1, 1}, {1, 5, 1}, {1, 1, 1} };

    //using the custom print function to print the matrix to the console
    A.print();
    //or
    // Matrix::print(A);
    return 0;
}

/** Output should be:


Matrix ( A )[3 x 3] is:

┌       1       1       1       ┐
|       1       5       1       |
└       1       1       1       ┘
*/