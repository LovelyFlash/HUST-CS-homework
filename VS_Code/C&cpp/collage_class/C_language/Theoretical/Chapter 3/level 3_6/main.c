#include <stdio.h>

int main() {
	/**********Begin**********/
    int x;
    scanf("%d", &x);
    if(x%4 == 0)
    {
        if(x%100 == 0)
        {
            if(x%400 == 0)
            {
                x = 29;
            }
            else
            {
                x=28;
            }
        }
        else
        {
            x = 29;
        }
    }
    else
    {
        x = 28;
    }
    printf("Jan: 31\nFeb: %d\nMar: 31\nApr: 30\nMay: 31\nJun: 30\nJul: 31\nAug: 31\nSep: 30\nOct: 31\nNov: 30\nDec: 31", x);
	/**********End**********/
	return 0;
}