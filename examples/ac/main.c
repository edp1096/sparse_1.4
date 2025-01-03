// src/smpl-test.c

/*
 * Simple test (and example) for Sparse
 *
 * This test builds a simple ladder network and then performs an AC analysis
 * to compute is transfer characteristics versus frequency.
 *
 * Assumes Sparse is configured for complex matrices and that
 * spSEPARATED_COMPLEX_VECTORS is NO.
 */

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include "spMatrix.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

int main(int argc, char **argv) {
    spMatrix A;
    struct spTemplate Stamp[3];
    spError err;
#if spSEPARATED_COMPLEX_VECTORS
    double bReal[3], bImag[3], xReal[3], xImag[3];
#else
    struct complex {
        double re;
        double im;
    } x[3], b[3];
#endif
    double f, omega;

    /* Create and build the matrix. */
    A = spCreate(2, 1, &err);
    if (err >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }
    spGetAdmittance(A, 1, 0, &Stamp[0]);
    spGetAdmittance(A, 1, 2, &Stamp[1]);
    spGetAdmittance(A, 2, 0, &Stamp[2]);
    if (spErrorState(A) >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }

    /* Drive the circuit at node 1. */
#if spSEPARATED_COMPLEX_VECTORS
    bReal[1] = 1.0;
    bImag[1] = 0.0;
    bReal[2] = 0.0;
    bImag[2] = 0.0;
#else
    b[1].re = 1.0;
    b[1].im = 0.0;
    b[2].re = 0.0;
    b[2].im = 0.0;
#endif

    /* Perform AC analysis over a range of frequencies. */
    // for (f = 0.0; f <= 100000.0; f += 1000.0) {
    for (f = 0.0; f <= 2000.0; f += 1000.0) {
        omega = 2.0 * M_PI * f;

        /* Load the matrix. */
        spClear(A);
        spADD_COMPLEX_QUAD(Stamp[0], 1 / 50.0, 1e-6 * omega);
        spADD_REAL_QUAD(Stamp[1], 1 / 200.0);
        spADD_COMPLEX_QUAD(Stamp[2], 1 / 50.0, 1e-6 * omega);

        /* Solve the matrix equations Ax = b for x. */
        err = spFactor(A);
        if (err >= spFATAL) {
            spErrorMessage(A, stderr, argv[0]);
            return 1;
        }
        // spSolve(A, (spREAL *)b, (spREAL *)x);
        // printf("f = %f, h = %f\n", f, sqrt(x[2].re * x[2].re + x[2].im * x[2].im));
#if spSEPARATED_COMPLEX_VECTORS
        spSolve(A, (spREAL *)bReal, (spREAL *)xReal, (spREAL *)bImag, (spREAL *)xImag);
        printf("f = %f, h = %f\n", f, sqrt(xReal[2] * xReal[2] + xImag[2] * xImag[2]));
#else
        spSolve(A, (spREAL *)b, (spREAL *)x);
        printf("f = %f, h = %f\n", f, sqrt(x[2].re * x[2].re + x[2].im * x[2].im));
#endif
    }
    return 0;
}
