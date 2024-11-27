#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CACULATE{
    char data;
    struct CACULATE *next;
}caculate;

caculate *creatlist();
void cal(caculate *head);

int main()
{
    caculate *head;
    head = createlist();
    cal(head);
    return 0;
}

caculate *createlist()
{
    caculate *p, *head = NULL;
    char x;
    scanf("%c", &x);
    while(x != '\n')
    {
        p = (caculate *)malloc(sizeof(caculate));
        p -> data = x;
        p -> next = head;
        head = p;
        scanf("%c", &x);
    }
    return head;
}

void cal(caculate *head)
{ 
    int result;
    for(caculate *p = head; p != NULL; p = p-> next)
    {
        if(p -> data >= '9' && p -> data <= '0')
        {
            ;
        }
    }
}