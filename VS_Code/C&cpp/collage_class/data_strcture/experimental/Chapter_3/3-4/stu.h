BiTNode *LocateNode(BiTree T, KeyType e)
// 查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL)
        return NULL;
    if (T->data.key == e)
        return T;
    BiTNode *p = LocateNode(T->lchild, e);
    if (p != NULL)
        return p;
    p = LocateNode(T->rchild, e);
    if (p != NULL)
        return p;
    return NULL;
    /********** End **********/
}
