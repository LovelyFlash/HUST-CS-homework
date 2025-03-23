#include <stdio.h>

int main()
{
    int a, b, c, score;
    scanf("%d %d %d", &a, &b, &c);
    score = a / 5 + b * 0.3 + c / 2;
    printf("%d", score);
    return 0;
}