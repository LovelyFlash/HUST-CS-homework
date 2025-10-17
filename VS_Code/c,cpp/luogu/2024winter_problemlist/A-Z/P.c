#include <stdio.h>
#include <string.h>

int main()
{
    int n, m, count;
    scanf("%d %d", &n, &m);
    char code[n][21], num[n][21];
    for (int i = 0; i < n; i++)
        scanf("%s %s", code[i], num[i]);
    getchar();
    for (count = 0; count < m;)
    {
        char c = getchar(), word[21];
        if (c == '\n')
        {
            count++;
            putchar('\n');
        }
        else if (c == '{')
        {
            int i = 0;
            for (; c != '}'; i++)
            {
                c = getchar();
                word[i] = c;
            }
            word[--i] = '\0';
            for (i = 0; i < n && strcmp(code[i], word); i++)
                ;
            printf("%s", num[i]);
        }
        else
            putchar(c);
    }
    return 0;
}