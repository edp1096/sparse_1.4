#include <stdio.h>
#include "spMatrix.h"

int main(int argc, char **argv) {
    spMatrix A;
    spError err;
    double x[8], b[8];  // Increased size for complex values

    /* Create the matrix with complex capability */
    A = spCreate(3, spCOMPLEX, &err);
    if (err >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }

    /* Load the complex matrix */
    spClear(A);

    /* First row elements */
    spADD_COMPLEX_ELEMENT(spGetElement(A, 1, 1), 2.0, 1.0);   // 2 + j
    spADD_COMPLEX_ELEMENT(spGetElement(A, 1, 2), 1.0, -1.0);  // 1 - j
    spADD_COMPLEX_ELEMENT(spGetElement(A, 1, 3), 3.0, 2.0);   // 3 + 2j

    /* Second row elements */
    spADD_COMPLEX_ELEMENT(spGetElement(A, 2, 1), -1.0, 1.0);  // -1 + j
    spADD_COMPLEX_ELEMENT(spGetElement(A, 2, 2), 3.0, 0.0);   // 3
    spADD_COMPLEX_ELEMENT(spGetElement(A, 2, 3), 2.0, -1.0);  // 2 - j

    /* Third row elements */
    spADD_COMPLEX_ELEMENT(spGetElement(A, 3, 1), 1.0, -2.0);  // 1 - 2j
    spADD_COMPLEX_ELEMENT(spGetElement(A, 3, 2), 2.0, 1.0);   // 2 + j
    spADD_COMPLEX_ELEMENT(spGetElement(A, 3, 3), 4.0, 0.0);   // 4

    printf("Original Complex Matrix:\n");
    spPrint(A, 0, 1, 1);

    if (spErrorState(A) >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }

    /* Set up the complex right-hand side vector b */
    b[0] = 0.0;
    b[1] = 0.0;
    b[2] = 3.0; /* real part */
    b[3] = 2.0; /* imaginary part */
    b[4] = 1.0;
    b[5] = -1.0;
    b[6] = 2.0;
    b[7] = 1.0;

    printf("\nRHS complex vector b:\n");
    for (int i = 1; i <= 3; i++) {
        printf("b[%d] = %.4f + %.4fj\n", i, b[2 * i], b[2 * i + 1]);
    }

    /* Factor the matrix */
    err = spFactor(A);
    if (err >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }

    printf("\nFactored Complex Matrix:\n");
    spPrint(A, 0, 1, 1);

    /* Solve the complex matrix equation Ax = b for x */
    spSolve(A, b, x);

    printf("\nSolution complex vector x:\n");
    for (int i = 1; i <= 3; i++) {
        printf("x[%d] = %.4f + %.4fj\n", i, x[2 * i], x[2 * i + 1]);
    }

    spDestroy(A);
    return 0;
}