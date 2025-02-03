#include <stdio.h>

int main()
{
    int num[3];
    scanf("%d %d %d", &num[0], &num[1], &num[2]);
    for (int i = 0; i < 3; i++)
    {
        for (int j = i; j < 3; j++)
        {
            if (num[j] < num[i])
            {
                int tem = num[j];
                num[j] = num[i];
                num[i] = tem;
            }
        }
    }
    for (int i = 0; i < 3; i++)
        printf("%d ", num[i]);
    return 0;
}