int insert(SqList &L, ElemType x)
{
    /**********begin**********/
    int i = 0, t;
    if (L.length == 0)
        L.elem[0] = x;
    for (; L.elem[i] <= x; i++)
        ;
    if (L.elem[i - 1] == x)
        return 0;
    for (t = L.length; t >= i; t--)
        L.elem[t] = L.elem[t - 1];
    L.elem[i] = x;
    L.length++;
    return 0;
    /**********end**********/
}
