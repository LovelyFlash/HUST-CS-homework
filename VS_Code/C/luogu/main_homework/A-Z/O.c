#include <stdio.h>

int main()
{
    int n, k;
    scanf("%d %d", &n, &k); // 读取 n 和 k

    int num[n];
    for (int i = 0; i < n; i++)
    { // 读取数组元素
        scanf("%d", &num[i]);
    }

    // 对数组进行简单排序（冒泡排序实现）
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (num[j] > num[j + 1])
            { // 如果前面的数大于后面的数，则交换
                int temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }

    int arr[n], j = 0;
    arr[0] = num[0];
    for (int i = 1; i < n - 1; i++)
    {
        if (arr[j] != num[i])
            arr[++j] = num[i];
    }
    arr[j] = '\0';

    if (k > j || k <= 0)
    { // 如果 k 超出范围，直接输出 NO RESULT
        printf("NO RESULT\n");
        return 0;
    }

    // 输出第 k 个最小值
    printf("%d\n", arr[k - 1]);

    return 0;
}
