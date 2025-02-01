#include <stdio.h>
#include <stdlib.h>

long long n, q, x, y;

// long long cmpfunc(const void *a, const void *b)
// {
//     return (*(long long *)a - *(long long *)b);
// }

int main()
{
    scanf("%lld %lld", &n, &q);
    long long equal[n][3], answer[n], num[200000] = {0};
    for (long long i = 0; i < n; i++)
    {
        scanf("%lldx%lld=%lld", &equal[i][0], &equal[i][1], &equal[i][2]);
        answer[i] = (equal[i][2] - equal[i][1]) / equal[i][0];
        num[answer[i]] = 1;
    }
    for (long long i = 0; i < q; i++)
    {
        scanf("%lld %lld", &x, &y);
        long long count = 0;
        for (long long i = x; i < y + 1; i++)
        {
            if (num[i])
                count++;
        }
        printf("%lld\n", count);
    }
    return 0;
}