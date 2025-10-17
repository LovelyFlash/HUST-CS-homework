#include<stdio.h>
#include<stdlib.h>

struct numNode{
    int num;
    struct numNode *next;
};

struct numNode *creatlist()
{
    struct numNode *p, *head, *tail;
    int x;
    head = NULL;
    tail = NULL;
    scanf("%d", &x);
    while(x != 0)
    {
        p = (struct numNode *)malloc(sizeof(struct numNode));
        p -> num = x;
        if(head == NULL)
            head = p;
        else
            tail -> next = p;
        tail = p;
        scanf("%d", &x);
    }
    if(tail != NULL)
        tail -> next = NULL;
    return head;
}

void print(struct numNode *head)
{
    struct numNode *p;
    p = head;
    while(p != NULL)
    {
            printf("%d\t", p -> num);
            p = p-> next;
    }
}

int main()
{
    struct numNode *head;
    head = creatlist();
    print(head);
}