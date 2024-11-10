#include<stdio.h>

void bubble_sort(int * a,int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(*(a+j+1) < *(a+j))
            {
                int temp = *(a + j + 1);
                *(a + j + 1) = *(a+j);
                *(a+j) = temp;
            }
        }
    }
}