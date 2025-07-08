#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    float c = (float)a + 0.1 * b, d = c / 1.9;
    printf("%d", (int)d);
    return 0;
}