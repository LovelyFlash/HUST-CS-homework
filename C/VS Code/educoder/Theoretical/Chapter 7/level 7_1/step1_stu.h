#include<stdio.h>

/*****请在下面补充函数 inArray、selectSort 和 outArray 的定义 *****/

void inArray(int arr[],int n)
{
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void selectSort(int arr[], int n)
{
    for(; n > 0; n--)
    {
        int k = 0, temp = 0;
        for(int i=0; i < n; i++)
        {
            if(arr[i] >= temp)
            {
                temp = arr[i];
                k = i;
            }
        }
        arr[k] = arr[n-1];
        arr[n-1] = temp;
        
    }
}

void outArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}