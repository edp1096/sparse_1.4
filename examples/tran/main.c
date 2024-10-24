#include <stdio.h>
#include <math.h>
#include "spMatrix.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#define STEP_SIZE 1e-6        // 1µs time step for smooth sine wave
#define SIMULATION_TIME 3e-3  // 3ms total simulation time (3 periods)
#define NUM_STEPS ((int)(SIMULATION_TIME / STEP_SIZE))

int main(int argc, char **argv) {
    spMatrix A;
    spError err;
    double x[3], b[3];

    // Circuit parameters
    const double R = 1000.0;     // 1kΩ resistor
    const double C = 1e-6;       // 1µF capacitor
    const double Vamp = 5.0;     // 5V amplitude
    const double freq = 1000.0;  // 1kHz frequency
    const double omega = 2.0 * M_PI * freq;
    const double G = 1.0 / R;  // Conductance

    // Time-stepping variables
    double t;
    double v_c = 0.0;  // Initial capacitor voltage
    double i_c;        // Capacitor current
    double v_in;       // Input voltage at current time step

    // Create matrix
    A = spCreate(2, 0, &err);
    if (err >= spFATAL) {
        spErrorMessage(A, stderr, argv[0]);
        return 1;
    }

    // Print header with circuit information
    printf("RC Circuit Transient Analysis\n");
    printf("Input: %.1fV sine wave at %.1fHz\n", Vamp, freq);
    printf("R = %.1f Ohm, C = %.1f uF\n", R, C * 1e6);
    printf("Expected phase shift: %.1f degrees\n", -atan(omega * R * C) * 180.0 / M_PI);
    printf("Expected amplitude ratio: %.3f\n", 1.0 / sqrt(1.0 + (omega * R * C) * (omega * R * C)));
    printf("\nTime(ms)\tVin(V)\tVout(V)\tIc(mA)\n");
    printf("0.000\t0.000\t0.000\t0.000\n");

    // Time-stepping loop
    for (int step = 1; step <= NUM_STEPS; step++) {
        t = step * STEP_SIZE;

        // Calculate input voltage for this time step
        v_in = Vamp * sin(omega * t);

        // Build the matrix for this time step
        spClear(A);

        // Stamp for resistor
        spADD_REAL_ELEMENT(spGetElement(A, 1, 1), G);
        spADD_REAL_ELEMENT(spGetElement(A, 1, 2), -G);
        spADD_REAL_ELEMENT(spGetElement(A, 2, 1), -G);
        spADD_REAL_ELEMENT(spGetElement(A, 2, 2), G + C / STEP_SIZE);

        // Set up right-hand side vector
        b[1] = v_in * G;               // Current source from voltage source
        b[2] = (C / STEP_SIZE) * v_c;  // Current source from capacitor

        // Solve the system
        err = spFactor(A);
        if (err >= spFATAL) {
            spErrorMessage(A, stderr, argv[0]);
            return 1;
        }

        spSolve(A, b, x);

        // Update capacitor voltage
        v_c = x[2];
        i_c = C * (v_c - x[2]) / STEP_SIZE;

        // Print results every 50 steps (about 20 points per cycle)
        if (step % 50 == 0) {
            printf("%.3f\t%.3f\t%.3f\t%.3f\n",
                   t * 1000.0,   // Time in milliseconds
                   v_in,         // Input voltage
                   v_c,          // Output voltage
                   i_c * 1000.0  // Current in milliamps
            );
        }
    }

    spDestroy(A);
    return 0;
}