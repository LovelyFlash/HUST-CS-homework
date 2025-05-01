#include <stdio.h>

int main()
{
    int i;
    double sum, a = 2.0, s;
    scanf("%lf", &s);
    for (i = 0; sum < s; i++)
    {
        sum += a;
        a *= 0.98;
    }
    printf("%d", i);
    return 0;
}