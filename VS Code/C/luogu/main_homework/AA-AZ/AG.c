#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    double *prefixScale = (double *)malloc((n + 1) * sizeof(double));
    double *prefixAngle = (double *)malloc((n + 1) * sizeof(double));

    prefixScale[0] = 1.0;
    prefixAngle[0] = 0.0;

    int type;
    double param;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %lf", &type, &param);
        if (type == 1)
        {
            // 拉伸变换
            prefixScale[i] = prefixScale[i - 1] * param;
            prefixAngle[i] = prefixAngle[i - 1];
        }
        else if (type == 2)
        {
            // 旋转变换
            prefixScale[i] = prefixScale[i - 1];
            prefixAngle[i] = prefixAngle[i - 1] + param;
        }
    }

    for (int q = 0; q < m; q++)
    {
        int i, j, x, y;
        scanf("%d %d %d %d", &i, &j, &x, &y);

        // 计算区间 [i, j] 内复合变换的参数：
        // 累积拉伸因子 S 和旋转角度 A
        double S = prefixScale[j] / prefixScale[i - 1];
        double A = prefixAngle[j] - prefixAngle[i - 1];

        double X = S * (x * cos(A) - y * sin(A));
        double Y = S * (x * sin(A) + y * cos(A));

        printf("%.3lf %.3lf\n", X, Y);
    }

    free(prefixScale);
    free(prefixAngle);

    return 0;
}
