#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODES 100000  // 最大节点数
#define MAX_LENGTH 11     // 节点名字最大长度

// 比较函数，用于 qsort 排序
int compare(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    char **yesterday = (char **)malloc(n * sizeof(char *));
    char **completed = (char **)malloc(m * sizeof(char *));
    char **new_discovered = (char **)malloc(k * sizeof(char *));
    char **result = (char **)malloc((n + k) * sizeof(char *));
    int result_count = 0;

    // 初始化动态数组
    for (int i = 0; i < n; i++)
    {
        yesterday[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
        scanf("%s", yesterday[i]);
    }

    for (int i = 0; i < m; i++)
    {
        completed[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
        scanf("%s", completed[i]);
    }

    for (int i = 0; i < k; i++)
    {
        new_discovered[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
        scanf("%s", new_discovered[i]);
    }

    // 排序昨天派遣潜艇的节点和已完成的节点
    qsort(yesterday, n, sizeof(char *), compare);
    qsort(completed, m, sizeof(char *), compare);

    // 使用双指针，找到昨天派遣潜艇但未完全探索的节点
    int completed_index = 0;
    for (int i = 0; i < n; i++)
    {
        // 使用双指针检查昨天派遣的节点是否已在已完成的节点中
        while (completed_index < m && strcmp(yesterday[i], completed[completed_index]) > 0)
        {
            completed_index++;
        }

        if (completed_index >= m || strcmp(yesterday[i], completed[completed_index]) != 0)
        {
            result[result_count++] = yesterday[i]; // 未完成，加入结果
        }
    }

    // 将新发现的节点加入结果集合
    for (int i = 0; i < k; i++)
    {
        result[result_count++] = new_discovered[i];
    }

    // 对结果集合按字典序排序
    qsort(result, result_count, sizeof(char *), compare);

    // 输出去重后的结果
    for (int i = 0; i < result_count; i++)
    {
        if (i == 0 || strcmp(result[i], result[i - 1]) != 0)
        {
            printf("%s\n", result[i]);
        }
    }

    // 释放动态分配的内存
    for (int i = 0; i < n; i++)
    {
        free(yesterday[i]);
    }
    for (int i = 0; i < m; i++)
    {
        free(completed[i]);
    }
    for (int i = 0; i < k; i++)
    {
        free(new_discovered[i]);
    }
    free(yesterday);
    free(completed);
    free(new_discovered);
    free(result);

    return 0;
}
