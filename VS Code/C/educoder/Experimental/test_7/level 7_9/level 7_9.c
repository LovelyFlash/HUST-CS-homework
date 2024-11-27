#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CACULATE{
    char data;
    struct CACULATE *next;
}caculate;

caculate *creatlist(caculate *headp);
void cal(caculate *head);

int main()
{
    caculate *head;
    head = createlist(head);
    cal(head);
    return 0;
}

caculate *createlist(caculate *headp)
{
    caculate *p, *head = NULL, *tail = NULL;
    p = headp;

    char x;
    scanf("%c", &x);
    while(x != '\n')
    {
        p = (caculate *)malloc(sizeof(caculate *));
        p -> data = x;
        if(head == NULL)
            head = p;
        else
            tail -> next = p;
        tail = p;
    }
    if(tail != NULL)
        tail -> next = NULL;
    head = headp;
    return head;
}

void cal(caculate *head)
{

}