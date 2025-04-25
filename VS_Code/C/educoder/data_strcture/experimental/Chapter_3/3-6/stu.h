BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL)
        return NULL;
    if (T->lchild != NULL && T->lchild->data.key == e)
        return T->rchild;
    if (T->rchild != NULL && T->rchild->data.key == e)
        return T->lchild;
    BiTNode* left = GetSibling(T->lchild, e);
    if (left != NULL)
        return left;
    BiTNode* right = GetSibling(T->rchild, e);
    if (right != NULL)
        return right;
    return NULL;
    /********** End **********/
}
