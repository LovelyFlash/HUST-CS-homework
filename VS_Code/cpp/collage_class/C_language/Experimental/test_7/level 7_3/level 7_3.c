#include <stdio.h>
#include <stdlib.h>

struct intNode{
    int c;
    struct intNode *next;
};

struct intNode *creatlist()
{
    struct intNode *head, *p;
    int x;
    head = NULL;
    scanf("%d", &x);
    while(x != 0)
    {
        p = (struct intNode *)malloc(sizeof(struct intNode));
        p -> c = x;
        p -> next = head;
        head = p;
        scanf("%d", &x);
    }
    return head;
}

void printList(struct intNode *head)
{
    struct intNode *p;
    p = head;
    while(p != NULL)
    {
        printf("%d\t", p -> c);
        p = p -> next;
    }
    printf("\n");
}

int main()
{
    struct intNode *head;
    head = creatlist();
    printList(head);
    return 0;
}