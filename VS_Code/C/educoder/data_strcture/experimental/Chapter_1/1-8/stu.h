status PriorElem(SqList L, ElemType e, ElemType &pre)
{
    // 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL) {
        return INFEASIBLE;
    }
    for (int i = 1; i < L.length; i++) {
        if (L.elem[i] == e) {
            pre = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR; // 没有前驱
    /********** End **********/
}