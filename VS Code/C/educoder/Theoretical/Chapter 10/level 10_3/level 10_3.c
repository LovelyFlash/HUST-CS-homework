#include<stdio.h>
#include<string.h>

struct web  /*  设计表示网址的结构  */
{
    /**********  Begin  **********/
    char short_name[100];
    char name[100];
    char URL[100];
	/**********   End   **********/
};

void sort(struct web webs[],int k, char n[]);



#define N  4      /*  网址表大小  */

int main()
{
	/**********  Begin  **********/
    struct web table[N], *p = table;
    char n[100];
    int k;
    for(int i = 0; i < N; i++)
    {
        scanf("%s %s %s", table[i].short_name, table[i].name, table[i].URL);
    }
    scanf("%s", n);
    sort(p, k, n);
	/**********   End   **********/
	return 0; 
}

void sort(struct web table[],int k, char n[])
{
	/**********  Begin  **********/
    char temp[100];
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N-i-1; j++)
        {
            if(strcmp(table[j].short_name, table[j + 1].short_name) > 0)
            {
                strcpy(temp, table[j+1].short_name);
                strcpy(table[j+1].short_name, table[j].short_name);
                strcpy(table[j].short_name, temp);
                strcpy(temp, table[j+1].name);
                strcpy(table[j+1].name, table[j].name);
                strcpy(table[j].name, temp);
                strcpy(temp, table[j+1].URL);
                strcpy(table[j+1].URL, table[j].URL);
                strcpy(table[j].URL, temp);
            }
        }
    }
    for(int i = 0; i < N; i++)
    {
        printf("%s %s %s\n", table[i].short_name, table[i].name, table[i].URL);
    }
    for(int i = 0; i < N; i++)
    {
        if (!strcmp(table[i].short_name , n))
        {
            k = i;
            break;
        }    
    }
    printf("%s", table[k].URL);
	/**********   End   **********/
}