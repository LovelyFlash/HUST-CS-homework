#include<string.h>

int isPalindrome(char *str)
//判断字符串str是否回文，是则返回1，否则返回0
{
/**********begin**********/
    int left = 0;
    int right = strlen(str) - 2;
    while (left < right) {
        if (str[left] != str[right]) {
            return 0; // 不是回文
        }
        left++;
        right--;
    }
    return 1; // 是回文
/********** end **********/
}