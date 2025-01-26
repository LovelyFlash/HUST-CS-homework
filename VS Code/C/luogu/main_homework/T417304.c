#include <stdio.h>
#include <string.h>

int cut(char *S, char *T, int ls, int rs, int lt, int rt);

int main()
{
    char S[1000], T[1000];
    int Q, ls, rs, lt, rt;
    scanf("%s %s %d", S, T, &Q);
    for (int i = 0; i < Q; i++)
    {
        scanf("%d %d %d %d", &ls, &rs, &lt, &rt);
        int code = cut(S, T, ls-1, rs-1, lt-1, rt-1);
        if (code == 2)
            printf("ovo\n");
        else if (code == 1)
            printf("yifusuyi\n");
        else
            printf("erfusuer\n");
    }
    return 0;
}

int cut(char *S, char *T, int ls, int rs, int lt, int rt)
{
    char cut_S[rs - ls + 2], cut_T[rt - lt + 2];
    for (int i = ls, j = 0; i <= rs; i++, j++)
        cut_S[j] = S[i];
    for (int i = lt, j = 0; i <= rt; i++, j++)
        cut_T[j] = T[i];
    if (strcmp(cut_S, cut_T) < 0)
        return 1;
    else if (strcmp(cut_S, cut_T) == 0)
        return 2;
    else
        return 0;
}