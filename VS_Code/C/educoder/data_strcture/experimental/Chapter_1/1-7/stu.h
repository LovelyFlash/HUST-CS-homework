int LocateElem(SqList L, ElemType e)
{
    // 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            return i + 1; // 返回位置序号，从1开始
        }
    }
    return 0; // 元素e不存在
    /********** End **********/
}