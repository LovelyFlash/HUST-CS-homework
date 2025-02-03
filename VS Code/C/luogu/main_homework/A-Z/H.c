#include <stdio.h>

int main()
{
    int x;
    scanf("%d", &x);
    int num[x];
    for (int i = 0; i < x; i++)
        scanf("%d", &num[i]);
    for (int i = 0; i < x; i++)
    {
        for (int j = i; j < x; j++)
        {
            if (num[j] < num[i])
            {
                int tem = num[j];
                num[j] = num[i];
                num[i] = tem;
            }
        }
    }
    float sum = 0;
    for (int i = 1; i < x - 1; i++)
        sum += (float)num[i];
    float ave = sum / (float)(x - 2);
    printf("%0.2f", ave);
    return 0;
}