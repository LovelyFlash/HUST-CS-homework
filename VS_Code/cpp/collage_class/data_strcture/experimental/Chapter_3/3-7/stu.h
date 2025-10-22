status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
// 插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (c.key <= e)
        return ERROR;
    BiTNode *newNode = (BiTNode *)malloc(sizeof(BiTNode));
    BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
    newNode->data = c;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    if (T == NULL)
    {
        return ERROR;
    }
    if (LR == -1)
    {
        p = T;
        T = newNode;
        newNode->rchild = p;
        return OK;
    }
    if (T->data.key == e)
    {
        if (LR == 0)
        {
            p = T->lchild;
            T->lchild = newNode;
            T->lchild->rchild = p;
        }
        else
        {
            p = T->rchild;
            T->rchild = newNode;
            T->rchild->lchild = p;
        }
        return OK;
    }
    if (InsertNode(T->lchild, e, LR, c) == OK)
        return OK;
    if (InsertNode(T->rchild, e, LR, c) == OK)
        return OK;
    free(newNode);
    return ERROR;
    /********** End **********/
}