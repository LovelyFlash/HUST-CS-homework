status InitList(LinkList &L)
{
    /********** Begin *********/
    if (L != NULL)
        return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    if (!L) return ERROR;
    L->next = NULL;
    return OK;
    /********** End **********/
}
