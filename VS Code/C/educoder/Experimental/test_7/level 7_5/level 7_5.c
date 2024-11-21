#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct scoreNode{
    char num[10];
    char name[10];
    int score[4];
    struct scoreNode *next;
};

struct scoreNode *createlist()
{
    struct scoreNode *p, *head, *tail;
    head = NULL;
    tail = NULL;
    char x[10], y[10]; 
    int z[4];
    scanf("%s %s %d %d %d %d", x, y, &z[0], &z[1], &z[2], &z[3]);
    while(x[0] == 'U')
    {
        p = (struct scoreNode *) malloc (sizeof(struct scoreNode *));
        strcpy(p -> num, x); 
        strcpy(p -> name, y); 
        strcpy(p -> score, z); 
        if(head ==NULL)
            head = p;
        else
            tail -> next = p;
        tail = p;
        scanf("%c", &x);
        scanf("%s %s %d %d %d %d", x, y, &z[0], &z[1], &z[2], &z[3]);
    }
    if(tail != NULL)
        tail -> next = NULL;
    return head;
}

void fun1()
{
    struct scoreNode *head = createlist();
}

void fun2()
{

}

void fun3_1()
{

}

void fun3_2()
{

}

void fun3_3()
{

}

void fun3_4()
{

}

void fun4()
{

}

void fun5()
{

}

void use_fun(int fun)
{
    if(fun == 1) fun1();
    else if(fun == 2) fun2();
    else if(fun == 31) fun3_1();
    else if(fun == 32) fun3_2();
    else if(fun == 33) fun3_3();
    else if(fun == 34) fun3_4();
    else if(fun == 4) fun4();
    else if(fun == 5) fun5();
    else return 0;
}

int main()
{
    int fun;
    scanf("%d", &fun);
    while(fun)
    {
        if(fun != 3)
            use_fun(fun);
        else
            use_fun(fun+30);
        scanf("%d", &fun);
    }
    return 0;
}