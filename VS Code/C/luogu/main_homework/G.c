#include <stdio.h>

int main()
{
    int x, i;
    scanf("%d", &x);
    for (i = 1; x > 1; i++)
        x /= 2;
    printf("%d", i);
    return 0;
}