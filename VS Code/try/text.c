#include <stdio.h>

int main()
{
    short x = 4, y = 0xcd, z = 0x20;
    char s[] = "hello", d;
    int a = 3, b = 4, c = 5;

    printf("%d", (x << 2 | y));
    return 0;
}