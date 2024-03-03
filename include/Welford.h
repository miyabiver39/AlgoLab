
#ifndef WELFORD_H
#define WELFORD_H

#define WINDOW_SIZE 10
#define TOTAL_POINTS 100

void recalculate(double window[], int size, double* mean, double* variance);
double kahan_sum(double* array, int size);

#endif
