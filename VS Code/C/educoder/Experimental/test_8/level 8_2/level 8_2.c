#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	FILE * fp;
	if(argc!=3)
    {
		printf("Arguments error!\n");
		exit(-1);
	}
	if((fp=fopen(argv[1],"r"))==NULL)
    {      /* fp指向filename */
		printf("Can't open %s file!\n", argv[1]);
		exit(-1);
	}
    int ch, i = 1;
    printf("%d ", i++);
    while ((ch = fgetc(fp)) != EOF)
    {
        if((i-1)%5 == 0)
        {
            char c = getchar();
        }
        if((char)ch == '\n')
    	{
            putchar(ch);            /* 向显示器中写从filename中读取的字符 */ 
            printf("%d ", i++);
        }
        else
            putchar(ch);
    }    

	fclose(fp);                        /* 关闭filename */ 
	return 0;
}
