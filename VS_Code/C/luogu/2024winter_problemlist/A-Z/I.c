#include <stdio.h>

int main()
{
    int x;
    scanf("%d", &x);
    int num[x + 1], prime[x];
    for (int i = 2; i <= x; i++)
        num[i] = 1;
    num[0] = 0, num[1] = 0;
    prime[0] = 0;
    for (int i = 2; i <= x; i++)
    {
        if (num[i] == 0)
            continue;
        else
            for (int j = i + 1; j <= x; j++)
            {
                if(num[j] == 0)
                    continue;
                else if (j % i == 0)
                    num[j] = 0;
                else
                    continue;
            }
    }
    int j = 0, sum = 0;
    for (int i = 2; i <= x; i++)
    {
        if (num[i] == 0)
            continue;
        else
            prime[j++] = i;
    }
    if (x > 1)
    {
        for (j = 0; x >= sum; j++)
        {
            sum += prime[j];
            if (x >= sum)
                printf("%d\n", prime[j]);
        }
        printf("%d", j-1);
    }
    else
        printf("0");

    return 0;
}