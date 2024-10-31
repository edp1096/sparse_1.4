#include <stdio.h>
#include "spMatrix.h"

int main(int argc, char **argv) {
    spMatrix A;
    spError err;
    double x[4], b[4];
    double R1 = 1000.0;
    double R2 = 2000.0;
    double Vin = 5.0;
    double G1 = 1.0 / R1;
    double G2 = 1.0 / R2;
    // struct spTemplate R1_template, R2_template;

    /* Create and build the matrix. */
    A = spCreate(2, 0, &err);
    if (err >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }

    /* Load the matrix. */
    spClear(A);
    spADD_REAL_ELEMENT(spGetElement(A, 1, 1), 2.0);
    spADD_REAL_ELEMENT(spGetElement(A, 1, 2), 1.0);
    spADD_REAL_ELEMENT(spGetElement(A, 1, 3), -1.0);

    spADD_REAL_ELEMENT(spGetElement(A, 2, 1), -3.0);
    spADD_REAL_ELEMENT(spGetElement(A, 2, 2), -1.0);
    spADD_REAL_ELEMENT(spGetElement(A, 2, 3), 2.0);

    spADD_REAL_ELEMENT(spGetElement(A, 3, 1), -2.0);
    spADD_REAL_ELEMENT(spGetElement(A, 3, 2), 1.0);
    spADD_REAL_ELEMENT(spGetElement(A, 3, 3), 2.0);

    spPrint(A, 0, 1, 1);  // Print A before spFactor

    if (spErrorState(A) >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }

    /* Set up the right-hand side vector b. */
    // b[1] = (1 / (R1 + R2)) * Vin;
    b[1] = 1;
    b[2] = 0.0;
    b[3] = 0.0;
    b[4] = 0.0;
    b[5] = 0.0;

    /* Solve the matrix equation Ax = b for x. */
    err = spFactor(A);
    if (err >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }
    spPrint(A, 0, 1, 1);  // Print A after spFactor

    // spSolve(A, b, x);

    // printf("Voltage at node 1 (V1): %.4f V\n", x[1]);
    // printf("Voltage at node 2 (V2, output): %.4f V\n", x[2]);
    // printf("Division ratio (R2 / (R1 + R2)): %.4f\n", x[2] / Vin);

    spDestroy(A);
    return 0;
}