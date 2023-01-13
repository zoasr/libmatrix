#include "../include/matrix.h"
using namespace std;

int main()
{
    //initializing a 3*3 matrix with the name "A"
    Matrix A(3, 3, "A");

    //showing a prompt to user to manually input the data during runtime
    A.input();
    //or
    // Matrix::input(A);

    //using the custom print function to print the matrix to the console
    A.print();
    return 0;
}