#include <stdio.h>

int main()
{
    int x, y, count = 0, tem, flag_write = 0, flag_ifread = 0;
    scanf("%d %d", &x, &y);
    int s[x];
    for (int i = 0; i < x; i++)
        s[i] = -1;
    for (int i = 0; i < y; i++)
    {
        scanf("%d ", &tem);
        for (int i = 0; i < x; i++)
        {
            if (s[i] == tem)
            {
                flag_ifread = 1;
                break;
            }
            else
                flag_ifread = 0;
        }
        if (flag_ifread)
        {
            flag_ifread = 0;
            continue;
        }
        else
        {
            s[flag_write % x] = tem;
            flag_write++;
            count++;
        }
    }
    printf("%d", count);
    return 0;
}