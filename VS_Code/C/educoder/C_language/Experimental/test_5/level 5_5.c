#include <stdio.h>

int main(void) {
    int M, N;
    scanf("%d %d", &M, &N);

    int a[M]; // 用于存储M个人的序号
    int visited[M]; // 标记数组，0表示未被移除，1表示已被移除
    int i, count = 0, pos = 0, x = 0; // count记录已移除人数，pos表示当前计数位置

    // 初始化数组a和visited
    for (i = 0; i < M; i++) {
        a[i] = i + 1;
        visited[i] = 0; // 所有元素初始状态为未移除
    }

    int b[M]; // 用于存储按顺序被移除的序号

    // 模拟约瑟夫环的过程
    while (count < M) { 
        int step = 0;
        while (step < N) { // 每次数到第N个人
            if (visited[pos] == 0) { // 如果该人未被移除
                step++; // 计数
            }
            if (step < N) { // 还未数到第N个人
                pos = (pos + 1) % M; // 继续向前移动
            }
        }
        
        b[x++] = a[pos]; // 将被移除的人的序号加入b数组
        visited[pos] = 1; // 标记该人已被移除
        count++; // 已移除人数加1
    }

    // 输出结果
            printf("%d", b[x-1]);

    return 0;
}
