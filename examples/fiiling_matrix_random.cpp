#include "..\src\matrix.h"
using namespace std;

int main()
{
    //initializing a 3*3 matrix with the name "A"
    Matrix A(3, 3, "A");

    //filling the matrix with random integer values inside a range
    A.fill_random_int(1, 100);
    //or
    //Matrix::fill_random_int(A, 1, 100);

    //using the custom print function to print the matrix to the console
    A.print();

    //filling the matrix with random double values inside a range
    A.fill_random(1, 100);
    //or
    //Matrix::fill_random(A, 1, 100);

    //using the custom print function to print the matrix to the console
    A.print();
    return 0;
}

/** Output should be Something like this:


Matrix ( A )[3 x 3] is:

┌       40      38      88      ┐


|       34      56      7       |


└       72      78      36      ┘




Matrix ( A )[3 x 3] is:

┌       12.6744 29.8356 95.2082 ┐


|       69.0223 6.85534 52.7856 |


└       94.3713 9.98544 40.087  ┘
*/