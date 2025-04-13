status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    if (i < 1)
        return ERROR;
    LinkList p = L;
    int j = 0;
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (p == NULL)
        return ERROR;
    LinkList newNode = (LinkList)malloc(sizeof(LinkList));
    if (newNode == NULL)
        return ERROR;
    newNode->data = e;
    newNode->next = p->next;
    p->next = newNode;
    return OK;
    /********** End **********/
}
