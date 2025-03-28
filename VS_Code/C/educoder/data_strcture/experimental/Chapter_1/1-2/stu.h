status DestroyList(SqList& L)
{
    if (L.elem != NULL)
    {
        free(L.elem);
        L.elem = NULL; // 将指针设置为NULL
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    else
    {
        return INFEASIBLE;
    }
}