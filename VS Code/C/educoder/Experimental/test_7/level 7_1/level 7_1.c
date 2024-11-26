#include<stdio.h>

char u[] = "UVWXYZ", v[] = "xyz";

struct T{
    int x;
    char c;
    char *t;
} a[] = {{11, 'A', u}, {100 , 'B', v}}, *p = a;

int main()
{
    int c;
    scanf("%d", &c);
    switch(c)
    {
        case 1:
            printf("%d", (++p) -> x);
            break;
        case 2:
            printf("%c", ((p++), (p->c)));
            break;
        case 3:
            printf("%c", ((*p++->t), (*p->t)));
            break;
        case 4:
            printf("%c", *(++p) -> t);
            break;
        case 5:
            printf("%c", *++p -> t);
            break;
        case 6:
            printf("%c", ++*p -> t);
            break;
    }
}