void TriSqList(SqList &A, SqList B, SqList C)
{
    /**********Begin**********/
    ElemType *c1 = A.elem, *c2 = B.elem, *c3 = C.elem;
    ElemType len1 = A.length, len2 = B.length, len3 = C.length;
    ElemType c[(len2 > len3 ? len2 : len3)], k = 0;
    for (int i = 0; i < len2; i++)
    {
        for (int j = 0; j < len3; j++)
        {
            if (c2[i] > c3[j])
                continue;
            else if (c2[i] == c3[j])
                c[k++] = c2[i];
            else
                break;
        }
    }
    int len = k, j = 0;
    for (int i = 0; i < len1; i++)
    {
        int flag = 0;
        for (int t = 0; t < len; t++)
            if (c1[i] == c[t])
                flag = 1;
        if (flag)
            continue;
        else
            c1[j++] = c1[i];
    }
    A.length = j;
    /**********End**********/
}