#include<stdio.h>

int main()
{
	/**********  Begin  **********/
	char c;
    int num[128] = {0}, sum;
    while((c = getchar()) != '\n')
    {
        num[c]++;
    }
    for(int i = 65; i <91; i++)
    {
        num[i] += num[i+32];
        num[i+32] = 0;
    }
    for(int i = 0; i < 128; i++)
    {
        if(num[i] != 0)
        {
            if(i>='0' && i<='9')
                printf("%c:%d\n", (char)i, num[i]);
            else if(i>='A' && i<='Z')
                printf("%c:%d\n", (char)i, num[i]);
            else sum += num[i];
        }
    }
    printf("others:%d\n", sum);
	/**********  End  **********/
	return 0; 
}
