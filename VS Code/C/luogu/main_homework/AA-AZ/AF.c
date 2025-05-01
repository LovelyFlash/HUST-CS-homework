#include <stdio.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int total_dx = 0, total_dy = 0;
    for (int i = 0; i < n; i++)
    {
        int dx, dy;
        scanf("%d %d", &dx, &dy);
        total_dx += dx;
        total_dy += dy;
    }

    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d %d\n", x + total_dx, y + total_dy);
    }

    return 0;
}
