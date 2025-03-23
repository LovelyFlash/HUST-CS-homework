status DestroyList(SqList& L)
{
    if (L.elem != NULL)
    {
        free(L.elem);
        return OK;
    }

    else
        return INFEASIBLE;

    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
}