status ListInsert(SqList &L, int i, ElemType e)
{
    // 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    if (i < 1 || i > L.length + 1) {
        return ERROR;
    }
    if (L.length >= L.listsize) {
        // 动态增加内存分配
        ElemType *newBase = (ElemType *) realloc(L.elem, (L.listsize + 10) * sizeof(ElemType));
        if (!newBase) {
            return OVERFLOW;
        }
        L.elem = newBase;
        L.listsize += 10;
    }
    for (int j = L.length; j >= i; j--) {
        L.elem[j] = L.elem[j - 1];
    }
    L.elem[i - 1] = e;
    L.length++;
    return OK;
    /********** End **********/
}