#include<stdio.h>
#include<stdlib.h>

void read_file(const char *filename);
void read_file_p(const char *filename);
void findfunc(const char *command);

int main(void)
{
    char command[20], *p = command;
    while(getchar() != EOF)
    {
        static int i = 0;
        *(p + i) = getchar();
    }
    findfunc(p);
    return 0;
}

void findfunc(const char *command)
{
    char command_1[] = "type_c /p";
    int flag = 1;
    for(int i = 0; i < 9; i++)
    {

    }
}