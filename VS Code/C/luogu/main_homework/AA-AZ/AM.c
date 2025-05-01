#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int main() {
    int t, n;
    scanf("%d %d", &t, &n);

    int p[MAX_N + 1]; // 依赖关系
    int ti[MAX_N + 1]; // 耗时
    int earliest[MAX_N + 1]; // 最早开始时间
    int latest_start[MAX_N + 1]; // 最晚开始时间
    int earliest_end[MAX_N + 1]; // 最早完成时间
    int latest_end[MAX_N + 1]; // 最晚完成时间

    // 输入依赖关系
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    // 输入耗时
    for (int i = 1; i <= n; i++) {
        scanf("%d", &ti[i]);
    }

    // 计算最早开始时间
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            earliest[i] = 1; // 无依赖，从时刻1开始
        } else {
            earliest[i] = earliest[p[i]] + ti[p[i]]; // 依赖菜品完成后开始
        }
    }

    // 计算最早完成时间并检查是否超过总时间t
    int max_earliest = 0;
    for (int i = 1; i <= n; i++) {
        earliest_end[i] = earliest[i] + ti[i] - 1;
        if (earliest_end[i] > max_earliest) {
            max_earliest = earliest_end[i];
        }
    }

    // 输出最早开始时间
    for (int i = 1; i <= n; i++) {
        printf("%d ", earliest[i]);
    }
    printf("\n");

    // 如果最早完成时间超过t，直接退出
    if (max_earliest > t) {
        return 0;
    }

    // 构建后继列表
    int succ[MAX_N + 1][MAX_N + 1]; // 后继列表
    int succ_count[MAX_N + 1] = {0}; // 每个菜品的后继数量

    for (int i = 1; i <= n; i++) {
        if (p[i] != 0) {
            succ[p[i]][succ_count[p[i]]++] = i;
        }
    }

    // 计算最晚完成时间和最晚开始时间
    for (int i = n; i >= 1; i--) {
        if (succ_count[i] == 0) {
            // 没有后继，最晚完成时间为t
            latest_end[i] = t;
        } else {
            // 有后继，取所有后继的最晚开始时间的最小值减1
            int min_start = t + 1;
            for (int j = 0; j < succ_count[i]; j++) {
                if (latest_start[succ[i][j]] < min_start) {
                    min_start = latest_start[succ[i][j]];
                }
            }
            latest_end[i] = min_start - 1;
        }
        latest_start[i] = latest_end[i] - ti[i] + 1;
    }

    // 输出最晚开始时间
    for (int i = 1; i <= n; i++) {
        printf("%d ", latest_start[i]);
    }
    printf("\n");

    return 0;
}