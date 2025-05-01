#include<stdio.h>

#define SIZE 100

void isPalindrome(char arr[], int len);

int main()
{
	/**** 输入字符串,调用函数isPalindrome判断是否为回文串，然后输出结果 *******/ 
    /**********  Begin ***********/
    char arr[SIZE], c;
    int i = 0;
    while((c = getchar()) != EOF)
    {
        arr[i++] = c;
    }
    arr[i] = '\0';
    isPalindrome(arr, i);
	/**********  End  **********/
	return 0;
}

/**** 在下面编写满足任务要求的递归函数isPalindrome，是回文返回1，不是返回0 *******/ 
/**********  Begin ***********/

void isPalindrome(char arr[], int len)
{
    int is_Pa = 1;
    for(int i = 0; i <= len/2; i++)
    {
        if(arr[i] != arr[len-1-i])
        {
            is_Pa = 0;
            break;
        } 
    }
    if(is_Pa) printf("Yes");
    else printf("No");
}


/**********  End  **********/
