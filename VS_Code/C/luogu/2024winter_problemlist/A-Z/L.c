#include <stdio.h>
#include <math.h>

int main()
{
    int n, q, flag = 0;
    scanf("%d %d", &n, &q);
    int item[n], need[q][2];
    for (int i = 0; i < n; i++)
        scanf("%d", &item[i]);
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (item[j] < item[i])
            {
                int t = item[j];
                item[j] = item[i];
                item[i] = t;
            }
        }
    }
    for (int i = 0; i < q; i++)
    {
        scanf("%d %d", &need[i][0], &need[i][1]);
        for (int j = 0; j < n; j++)
        {
            if ((item[j] % (int)pow(10, need[i][0])) == need[i][1])
            {
                printf("%d\n", item[j]);
                flag = 1;
                break;
            }
            else
                flag = 0;
        }
        if (!flag)
            printf("-1\n");
    }
}