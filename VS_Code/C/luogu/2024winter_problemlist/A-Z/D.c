#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%d", &a);
    b = !(a % 2);
    c = (a > 4) && (a <= 12);
    if (b & c)
        printf("1 ");
    else
        printf("0 ");
    if (b | c)
        printf("1 ");
    else
        printf("0 ");
    if (b == 0 && c == 1 || b == 1 && c == 0)
        printf("1 ");
    else
        printf("0 ");
    if (b == 0 && c == 0)
        printf("1");
    else
        printf("0");
}