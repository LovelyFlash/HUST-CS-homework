#include <stdio.h>
#include <stdlib.h>
int time = 0, tem_sum = 0, sum[4] = {0, 0, 0, 0};
int current_sum = 0;
#define mi(x, y) ((((x) - (y)) > 0) ? ((x) - (y)) : ((y) - (x)))

void least_time(int *sub, int sum, int start, int n, int k, int count)
{
    if (count == k) // 找到与总时间之和的一半最接近的时间之和，即为最短时间
    {
        if (mi(tem_sum, sum / 2) > mi(current_sum, sum / 2) && (double)current_sum >= (double)sum / 2)
            tem_sum = current_sum;
        return;
    }
    for (int i = start; i < n; i++) // 遍历所有（n个时间中的k个）时间之和，也就是遍历C(n,k)种组合
    {
        current_sum += sub[i];
        least_time(sub, sum, i + 1, n, k, count + 1);
        current_sum -= sub[i];
    }
}

int main()
{
    int s1, s2, s3, s4;
    scanf("%d %d %d %d", &s1, &s2, &s3, &s4);
    int A[s1], B[s2], C[s3], D[s4], num[] = {s1, s2, s3, s4};
    int *sub[] = {&A[0], &B[0], &C[0], &D[0]};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < num[i]; j++)
        {
            scanf("%d", (sub[i] + j));
            sum[i] += *(sub[i] + j);
        }
        tem_sum = sum[i];                         // 求出该任务所有时间之和
        for (int k = 1; k <= 1 + num[i] / 2; k++) // 从1开始找到C(n,k)中时间组合中的最接近一半的时间
        {
            if (tem_sum == sum[i] / 2) // 如果在中途发现有组合相加可以直接等于一半时间，就直接输出
                break;
            least_time(sub[i], sum[i], 0, num[i], k, 0);
        }
        time += tem_sum; // 每门科目的最小时间相加
    }
    printf("%d", time);
    return 0;
}