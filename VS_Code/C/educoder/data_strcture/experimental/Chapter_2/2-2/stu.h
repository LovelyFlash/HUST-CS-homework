status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L != NULL)
    {
        LinkList p = L->next, q;
        while (p != NULL)
        {
            q = p->next;
            free(p);
            p = q;
        }
        free(L);
        L = NULL;
        return OK;
    }
    else return INFEASIBLE;
    /********** End **********/
}
