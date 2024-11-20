#include <stdio.h>

int main()
{
    int i = 0, j = 0, k = 1, n, flag;
    int matrix[100][100] = {0};
    scanf("%d", &n);
    if(n == 0) printf("0");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
        }
    }
    for(flag = 2*n -1; flag > 0; flag--)
    {   
        if((flag % 4) == 1)
        {
            for(; matrix[i][j] == 0 && j < n; ++j)
            matrix[i][j] = k++;
            j--, i++;
        }
        else if((flag % 4) == 0)
        {
            for(; matrix[i][j] == 0 && i < n; ++i)
            matrix[i][j] = k++;
            i--, j--;
        }
        else if((flag % 4) == 3)
        {
            for(; matrix[i][j] == 0 && j < n && j > -1; --j)
            matrix[i][j] = k++;
            j++, i--;
        }
        else if((flag % 4) == 2)
        {
            for(; matrix[i][j] == 0 && i < n && i > -1; --i)
            matrix[i][j] = k++;
            i++, j++;
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(j != n-1)    printf("%d ", matrix[i][j]);
            else printf("%d\n", matrix[i][j]);
        }
    }
}