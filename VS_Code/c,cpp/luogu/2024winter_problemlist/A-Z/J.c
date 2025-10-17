#include <stdio.h>

int main()
{
    int x, y, count = 0;
    scanf("%d %d", &x, &y);
    for (int i = 1; i <= x; i++)
    {
        for (int j = i; j != 0; j /= 10)
        {
            if ((j % 10) == y)
                count++;
        }
    }
    printf("%d", count);
    return 0;
}