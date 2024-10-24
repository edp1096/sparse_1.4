#include <stdio.h>
#include "spMatrix.h"

int main(int argc, char **argv) {
    spMatrix A;
    spError err;
    double x[3], b[3];
    double R1 = 1000.0;
    double R2 = 1000.0;
    // double Vin = 5.0;
    double G1 = 1.0 / R1;
    double G2 = 1.0 / R2;
    // struct spTemplate R1_template, R2_template;

    /* Create and build the matrix. */
    A = spCreate(2, 0, &err);
    if (err >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }

    // /* Get templates for resistors */
    // spGetAdmittance(A, 1, 2, &R1_template);  // R1: node1 - node2
    // spGetAdmittance(A, 2, 0, &R2_template);  // R2: node2 - ground

    /* Load the matrix. */
    spClear(A);
    spADD_REAL_ELEMENT(spGetElement(A, 1, 1), G1);
    spADD_REAL_ELEMENT(spGetElement(A, 1, 2), -G1);
    spADD_REAL_ELEMENT(spGetElement(A, 2, 1), -G1);
    spADD_REAL_ELEMENT(spGetElement(A, 2, 2), G1 + G2);
    // spADD_REAL_QUAD(R1_template, G1);
    // spADD_REAL_QUAD(R2_template, G2);

    if (spErrorState(A) >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }

    for (double Vin = 1.0; Vin <= 10.0; Vin += 1.0) {
        /* Set up the right-hand side vector b. */
        b[1] = (1 / (R1 + R2)) * Vin;
        b[2] = 0.0;

        /* Solve the matrix equation Ax = b for x. */
        err = spFactor(A);
        if (err >= spFATAL) {
            spErrorMessage(A, stderr, argv[0]);
            return 1;
        }

        spSolve(A, b, x);

        printf("Voltage at node 1 vs node 2: %.4f V / %.4f V\n", x[1], x[2]);
        // printf("Division ratio (R2 / (R1 + R2)): %.4f\n", x[2] / Vin);
    }

    spDestroy(A);
    return 0;
}