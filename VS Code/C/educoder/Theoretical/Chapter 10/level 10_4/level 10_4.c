#include <stdio.h>
#include <stdlib.h>

struct charNode{
    char c;
    struct charNode *next;
};

struct charNode *creatlist()
{
    struct charNode *head, *tail, *p;
    char x;
    head = NULL;
    tail = NULL;
    scanf("%c", &x);
    while(x != '\n')
    {
        p = (struct charNode *)malloc(sizeof(struct charNode));
        p -> c = x;
        if(head ==NULL)
            head = p;
        else
            tail -> next = p;
        tail = p;
        scanf("%c", &x);
    }
    if(tail != NULL)
        tail -> next = NULL;
    return head;
}

int printList(struct charNode *head)
{
    int i = 0;
    struct charNode *p;
    p = head;
    while(p != NULL)
    {
        printf("%c ", p -> c);
        p = p -> next;
        i++;
    }
    printf("\n");
    return i;
}

void editlist(int len, struct charNode *head)
{
    char temp;
    scanf("%c", &temp);
    
}

void print(int len, struct charNode *head)
{
    char str[len];
    struct charNode *p;
    p = head;
    while(p != NULL)
    {
        static int i = 0;
        str[i++] = (p -> c);
        p = p -> next;
    }
    printf("%s", str);
}

int main()
{
    struct charNode *head;
    head = creatlist();
    int len = printList(head);
    print(len, head);
    editlist(len, head);
    return 0;
}