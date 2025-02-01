#include <stdio.h>

int main()
{
    int x;
    scanf("%d", &x);
    if (x < 6)
        printf("Local");
    else
        printf("Luogu");
    return 0;
}