status ListTraverse(SqList L)
{
    // 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem == NULL)
    {
        return INFEASIBLE;
    }
    for (int i = 0; i < L.length; i++)
    {
        printf("%d", L.elem[i]);
        if (i != L.length - 1)
            printf(" ");
    }
    return OK;
    /********** End **********/
}