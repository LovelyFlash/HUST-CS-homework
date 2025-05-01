status ListLength(SqList &L)
{
    // 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem==NULL) {
        return INFEASIBLE;
    }
    return L.length;
    /********** End **********/
}