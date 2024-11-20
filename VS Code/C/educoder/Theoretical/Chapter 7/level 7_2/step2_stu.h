#include<stdio.h>

void move(int arr[],int n,int k){
	/**********  Begin  **********/
    int temp[n];
    for(int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }
    for(int j = 0; j < k; j++)
        {
            arr[n-k+j] = temp[j];
        }
    for(int j = 0; j < n-k; j++)
        {
            arr[j] = temp[k+j];
        }
	/**********  End  **********/
}
