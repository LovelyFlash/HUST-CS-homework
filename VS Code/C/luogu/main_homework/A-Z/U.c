#include <stdio.h>
void output(int x)
{
    int num[16] = {0};
    for (int i = 0; x != 0; i++)
    {
        num[i] = x % 2;
        x /= 2;
    }
    int flag = 0;
    for (int i = 14; i >= 0; i--)
    {
        if (num[i] && i > 1)
        {
            if (flag)
            {
                putchar('+');
                flag = 0;
            }
            printf("2(");
            output(i);
            printf(")");
            flag = 1;
        }
        else if (num[i] && i == 1)
        {
            if (flag)
            {
                putchar('+');
                flag = 0;
            }
            printf("2");
            flag = 1;
        }
        else if (num[i] && i == 0)
        {
            if (flag)
            {
                putchar('+');
                flag = 0;
            }
            printf("2(0)");
        }
    }
}

int main()
{
    int x;
    scanf("%d", &x);
    output(x);
    return 0;
}