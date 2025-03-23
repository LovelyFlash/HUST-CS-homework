int insert(SqList &L, ElemType x)
{
    int i = 0, t;

    if (L.length >= L.listsize)
    {
        ElemType *newBase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newBase)
            return -1;
        L.elem = newBase;
        L.listsize += LISTINCREMENT;
    }
    if (L.length == 0)
    {
        L.elem[0] = x;
        L.length++;
        return 0;
    }
    while (i < L.length && L.elem[i] <= x)
    {
        i++;
    }

    if (i > 0 && L.elem[i - 1] == x)
        return 0;

    for (t = L.length; t > i; t--)
    {
        L.elem[t] = L.elem[t - 1];
    }
    L.elem[i] = x;
    L.length++;

    return 0;
}
