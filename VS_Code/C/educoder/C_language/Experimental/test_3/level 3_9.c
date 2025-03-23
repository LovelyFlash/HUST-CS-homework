/*
任务描述
本关任务：实验课本P85  程序设计第（5）题
编写一个能打印n行杨辉三角的小程序。

编程要求
根据提示，在右侧编辑器补充代码，使之能打印n行(1≤n≤10)杨辉三角。

测试说明
平台会对你编写的代码进行测试：

测试输入：9；
预期输出：
                  1
                1   1
              1   2   1
            1   3   3   1
          1   4   6   4   1
        1   5   10  10  5   1
      1   6   15  20  15  6   1
    1   7   21  35  35  21  7   1
  1   8   28  56  70  56  28  8   1
1   9   36  84  126 126 84  36  9   1

提示：
参考实验课本85-86页的公式和格式

补充：
最后一行左边不能有空格

开始你的任务吧，祝你成功！
*/
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int triangle[11][11] = {0};
    for (int i = 0; i <= n; i++) 
    {
        triangle[i][0] = 1;
        triangle[i][i] = 1;
        for (int j = 1; j < i; j++) 
        {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
    for (int i = 0; i <= n; i++) 
    {
        for (int k = 0; k < n - i; k++) {
            printf("  ");
        }
        for (int j = 0; j <= i; j++) 
        {
                printf("%-4d", triangle[i][j]);
        }
        if(i < n)
        printf("\n");
    }
    return 0;
}
