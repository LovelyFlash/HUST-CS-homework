status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL)
        return ERROR;
    if (T->data.key == e)
    {
        if (T->lchild == NULL && T->rchild == NULL) // 度为0
        {
            free(T);
            T = NULL;
            return OK;
        }
        else if (T->lchild == NULL || T->rchild == NULL) // 度为1
        {
            BiTree temp = T;
            T = (T->lchild != NULL) ? T->lchild : T->rchild;
            free(temp);
            return OK;
        }
        else // 度为2
        {
            BiTree temp = T->lchild;
            while (temp->rchild != NULL)
            temp = temp->rchild;
            temp->rchild = T->rchild;
            temp = T;
            T = T->lchild;
            free(temp);
            return OK;
        }
    }
    if (DeleteNode(T->lchild, e) == OK)
        return OK;
    if (DeleteNode(T->rchild, e) == OK)
        return OK;
    return ERROR;
    /********** End **********/
}