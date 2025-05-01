status InitList(SqList &L)
{
    if (L.elem != NULL)
        return INFEASIBLE; 
    
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        return OVERFLOW;
    
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
}
