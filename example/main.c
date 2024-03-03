#include "../include/hello.h"
#include "../include/Welford.h"

#include <stdio.h>

int main()
{

    print_hello_world();

    double data[TOTAL_POINTS];        // 100個のデータポイントを想定
    double window[WINDOW_SIZE] = {0}; // スライディングウィンドウ
    int dataIndex = 0;

    // データポイントの生成（例として1から100までの整数）
    for (int i = 0; i < TOTAL_POINTS; i++)
    {
        data[i] = i;
    }

    double mean = 0.0, variance = 0.0;
    for (int i = 0; i < TOTAL_POINTS; i++)
    {
        // 新しいデータポイントをウィンドウに追加
        window[dataIndex % WINDOW_SIZE] = data[i];
        dataIndex++;

        // ウィンドウが満たされたら平均と分散を再計算
        if (i >= WINDOW_SIZE - 1)
        {
            recalculate(window, WINDOW_SIZE, &mean, &variance);
            printf("データポイント %d: 平均 = %f, 分散 = %f\n", i + 1, mean, variance);
        }
    }

    return 0;
}
