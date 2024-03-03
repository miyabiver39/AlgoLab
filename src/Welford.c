#include <stdio.h>
#include "../include/Welford.h"

// Kahanの加算アルゴリズムを用いた合計計算
double kahan_sum(double *array, int size)
{
    double sum = 0.0;
    double c = 0.0; // 補償
    for (int i = 0; i < size; i++)
    {
        double y = array[i] - c; // 補償された値
        double t = sum + y;      // sumは大きい値、yは小さい値
        c = (t - sum) - y;       // (t - sum)は高次ビット、-yは低次ビットの損失
        sum = t;
    }
    return sum;
}

// ウィンドウ内のデータポイントから平均と分散を再計算
void recalculate(double window[], int size, double *mean, double *variance)
{
    double sum = kahan_sum(window, size);
    *mean = sum / size;

    double M2 = 0.0;
    double c = 0.0; // 分散計算のための補償

    // XXX:ウィンドウ内のデータポイントに対して0から再計算している。
    // 本来であれば、データポイントの更新の際に、逐次的に計算されるべき。
    // 修正方法を検討するとして、今はこのままにする。
    for (int i = 0; i < size; i++)
    {
        double y = (window[i] - *mean) * (window[i] - *mean) - c;
        double t = M2 + y;
        c = (t - M2) - y;
        M2 = t;
    }
    *variance = M2 / (size - 1);
}
