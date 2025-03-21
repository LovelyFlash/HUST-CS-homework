#include <stdio.h>

//请根据主程序流程，补全此函数
//冰雹产生并输出函数
//注意：输出每个冰雹数时，请按5位对齐输出
void hailstone(int n) 
{
    printf("Hailstone generated by %d:\n",n);
    /**********  Begin **********/
    int count = 1;
    while(n != 1)
    {
        if((n % 2) == 1)
        {
            printf("%5d",n);
            n = 3*n +1;
        }
        else if((n % 2) == 0)
        {
            printf("%5d",n);
            n = n/2;     
        }
        if(((count++)%6) == 0)
            printf("\n");
        
    }
    /**********  End  **********/
    printf("%5d\n",n);
	printf("Number of hailstone generated:%d",count);
}
