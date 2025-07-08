#include <stdio.h>
#include <stdlib.h>

long long n, q, x, y, i, k;

long long lower_bound(long long *arr, long long n, long long target)
{
    long long left = 0, right = n;
    while (left < right)
    {
        long long mid = left + (right - left) / 2;
        if (arr[mid] <= target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

long long upper_bound(long long *arr, long long n, long long target)
{
    long long left = 0, right = n;
    while (left < right)
    {
        long long mid = left + (right - left) / 2;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int cmpfunc(const void *a, const void *b)
{
    return (*(long long *)a - *(long long *)b);
}

int main()
{
    scanf("%lld %lld", &n, &q);
    long long equal[n][3], answer[n];
    for (long long i = 0; i < n; i++)
    {
        scanf("%lldx%lld=%lld", &equal[i][0], &equal[i][1], &equal[i][2]);
        answer[i] = (equal[i][2] - equal[i][1]) / equal[i][0];
    }
    qsort(answer, n, sizeof(long long), cmpfunc);
    for (i = 0, k = 0; i < n; i++)
    {
        if (answer[k] == answer[i])
            continue;
        answer[++k] = answer[i];
    }
    answer[++k] = '\0';
    for (long long i = 0; i < q; i++)
    {
        scanf("%lld %lld", &x, &y);
        long long count = 0;
        long long l = upper_bound(answer, k, x);
        long long r = lower_bound(answer, k, y);
        printf("%lld\n", r > l ? r - l : 0);
    }
    return 0;
}