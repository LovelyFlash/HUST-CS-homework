/*
任务描述
本关任务：完善实验指导书P142的求解约瑟夫问题的源程序：M个人围成一圈，从第一个人开始一次从1至N报数，每当报数为N时报数人出圈，直到圈中只剩下一个人为止。

本任务改为键盘输入 M 和 N 。

示例
输入（第一个数为M，第二个数为N）：
5 3
输出：(每个数占6位宽，第1行为出圈人编号，第2行为最后留在圈中人的编号)
  3   1   5   2
  4

开始你的任务吧，祝你成功！


*/
#include <stdio.h>

int main(void) {
    int M, N;
    scanf("%d %d", &M, &N);

    int a[M]; // 用于存储M个人的序号
    int b[M]; // 用于存储按顺序被移除的序号
    int i, j, x = 0; // i, j是循环计数器，x用于记录b数组的位置

    // 初始化数组a，表示每个人的序号
    for (i = 0; i < M; i++) {
        a[i] = i + 1;
    }

    int remaining = M; // 剩余人数
    int pos = 0; // 当前计数位置

    // 模拟约瑟夫环的过程
    while (remaining > 0) {
        // 计数到第N个人
        pos = (pos + N - 1) % remaining;
        b[x++] = a[pos]; // 将被移除的人的序号加入b数组

        // 移除当前被选中的人，将后面的人依次前移
        for (j = pos; j < remaining - 1; j++) {
            a[j] = a[j + 1];
        }
        
        remaining--; // 剩余人数减1
    }

    // 输出结果
    for (i = 0; i < M; i++) {
        printf("%6d", b[i]);
        if (i < M - 2) {
            printf("");
        } else {
            printf("\n");
        }
    }

    return 0;
}

