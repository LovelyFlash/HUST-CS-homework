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

void editlist(int len, struct charNode *head, char *str)
{
    char temp;
    scanf("%c", &temp);
    int note = -1, flag = 128;
    for(int i = 0; i < len; i++)
    {
        if(*(str + i) == temp)
        {
            for(int j = i; j < len; j++)
            {
                *(str + j) = *(str+j+1);
            }
            len--;
            note = -1;
            break;
        }
        else
        {
            int tem;
            if((int)(*(str +i) - temp)<0) 
                tem = -(int)(*(str +i) - temp);
            else tem = (int)(*(str +i) - temp);
            if(flag > tem)
            {
                flag = tem;
                note = i;
            }
        }
    }
    for(int i = 0; i < len; i++)
    {
        if(i == note)
            printf("%c%c", *(str + i), temp);
        else
            printf("%c", *(str + i)); 
    }
}

char *print(int len, struct charNode *head) 
{
    char *str = (char *)malloc(len + 1); 
    struct charNode *p = head;
    int i = 0;
    while (p != NULL) {
        str[i++] = p->c;
        p = p->next;
    }
    str[i] = '\0'; 
    printf("%s\n", str);
    return str;
}


int main()
{
    struct charNode *head;
    head = creatlist();
    int len = printList(head);
    char *x = print(len, head);
    editlist(len, head, x);
    return 0;
}