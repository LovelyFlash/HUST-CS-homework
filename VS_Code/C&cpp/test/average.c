#include<stdio.h>
int main()
{
	/**********  Begin  **********/
    int n = 0, k, a ;
    float m, j = 0.0;
    for(k=1 ; k<=10; k++)
    {
        scanf("%d", &a);
        if(a > 0)
        {
            n = n + a;
            j++;
        }
        else
        {
            a = 0;
        }
    }
    m = n;
    if(j != 0)
    {
        printf("累加和:%d\n平均值:%.1f", n, m/j);
    }
    else
    {
        printf("累加和:0\n平均值:0");
    }
	/**********  End  **********/
    return 0;
}