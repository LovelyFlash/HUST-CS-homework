int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L == NULL)
        return INFEASIBLE;
    int length = 0;
    LinkList p = L->next;
    while (p != NULL)
    {
        length++;
        p = p->next;
    }
    return length;
    /********** End **********/
}
