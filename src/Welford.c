#include <stdio.h>
#include "../include/Welford.h"

// ウィンドウ内のデータポイントから平均と分散を再計算
void recalculate(double window[], int size, double* mean, double* variance) {
    double sum = 0.0;
    for(int i = 0; i < size; i++) {
        sum += window[i];
    }
    *mean = sum / size;

    double M2 = 0.0;
    for(int i = 0; i < size; i++) {
        double delta = window[i] - *mean;
        M2 += delta * delta;
    }
    *variance = M2 / (size - 1);
}

