#include <stdio.h>
#include <string.h>

int main()
{
    char num[100], tem[100], min[100], i;
    scanf("%s", num);
    int len = strlen(num);
    strcpy(min, num);
    for (i = 0; num[i] != '1' && i < len; i++);

    for (int j = i + 1; j < len; j++)
    {
        strcpy(tem, num);
        for (int n = i; n <= (i + j) / 2; n++)
        {
            char t = tem[n];
            tem[n] = tem[i + j - n];
            tem[i + j - n] = t;
        }
        if (strcmp(min, tem) > 0)
            strcpy(min, tem);
    }

    printf("%s\n", min);
    return 0;
}