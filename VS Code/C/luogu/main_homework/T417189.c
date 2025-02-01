#include <stdio.h>
#include <stdlib.h>

int lower_bound(int *arr, int n, int target)
{
    int left = 0, right = n;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int upper_bound(int *arr, int n, int target)
{
    int left = 0, right = n;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

// 修复比较函数
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    qsort(arr, n, sizeof(int), cmpfunc); // 修正排序函数

    while (m--)
    {
        int op, x, y;
        scanf("%d", &op);
        switch (op)
        {
        case 1:
        {
            scanf("%d", &x);
            int l = lower_bound(arr, n, x);
            int r = upper_bound(arr, n, x);
            printf("%d\n", r > l ? r - l : 0);
            break;
        }
        case 2:
        {
            scanf("%d %d", &x, &y);
            int l = lower_bound(arr, n, x);
            int r = upper_bound(arr, n, y);
            printf("%d\n", r > l ? r - l : 0);
            break;
        }
        case 3:
        {
            scanf("%d %d", &x, &y);
            int l = lower_bound(arr, n, x);
            int r = lower_bound(arr, n, y);
            printf("%d\n", r > l ? r - l : 0);
            break;
        }
        case 4:
        {
            scanf("%d %d", &x, &y);
            int l = upper_bound(arr, n, x);
            int r = upper_bound(arr, n, y);
            printf("%d\n", r > l ? r - l : 0);
            break;
        }
        case 5:
        {
            scanf("%d %d", &x, &y);
            int l = upper_bound(arr, n, x);
            int r = lower_bound(arr, n, y);
            printf("%d\n", r > l ? r - l : 0);
            break;
        }
        }
    }
    free(arr);
    return 0;
}