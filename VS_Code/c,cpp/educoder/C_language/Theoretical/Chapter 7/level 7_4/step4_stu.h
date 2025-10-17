#include<stdio.h>

void strnCpy(char t[],char s[],int n){
	/**********  Begin  **********/
    int i = 0;
    for(; i < n; i++)
    {
        t[i] = (char)s[i];
    }
    t[i] = '\0';
	/**********  End  **********/
}
