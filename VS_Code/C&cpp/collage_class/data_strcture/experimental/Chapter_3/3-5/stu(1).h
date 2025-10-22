status Assign(BiTree &T, KeyType e, TElemType value)
// 实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    static int i = 1;
    for (; i <= e; i *= 2);
    i /= 2;
    if (value.key < e)
        return ERROR;
    if (T == NULL)
        return ERROR;
    while (i >= 2)
    {
        if (e % i < i / 2)
        {
            if (Assign(T->lchild, e > i ? e - i : e, value) == OK)
                return OK;
        }
        else
        {
            if (Assign(T->rchild, e > i ? e - i : e, value) == OK)
                return OK;
        }
    }
    if (i == 1)
    {
        T->data = value;
        i--;
        return OK;
    }
    return ERROR;
    /********** End **********/
}
