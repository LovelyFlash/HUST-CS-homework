#include <stdio.h>

//请根据step3_main.cpp中的主函数流程，补全此函数
int digit(long n, int k)
{
	/**********  Begin  **********/
    int i=1;
    for(; n/10 != 0; i++);
    if(k > i) return -1;
    else
    {
        int a = (n>>(k-1))%10;
        return a;
    }
    /**********  End  **********/
}
