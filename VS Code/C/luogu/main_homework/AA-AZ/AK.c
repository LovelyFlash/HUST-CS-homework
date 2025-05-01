#include <stdio.h>
#include <stdlib.h>

long long calc_cost(int ti, int ci, int target)
{
    if (ti <= target)
        return 0;
    return (long long)(ti - target) * ci;
}

int binary_search(int n, long long m, int k, int *t, int *c)
{
    int left = k, right = 100000;

    while (left < right)
    {
        int mid = (left + right) / 2;
        long long total_cost = 0;

        for (int i = 0; i < n; i++)
        {
            total_cost += calc_cost(t[i], c[i], mid);
            if (total_cost > m)
                break;
        }

        if (total_cost <= m)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int t[n], c[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &t[i], &c[i]);
    }

    int result = binary_search(n, m, k, t, c);

    printf("%d\n", result);

    return 0;
}
