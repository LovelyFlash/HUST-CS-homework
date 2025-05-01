status JudgeBiTree(BiTree T)
// 判断二叉树T是否为二叉排序树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    status flag = TRUE; // 标志变量

    if (T == NULL) // 空树是二叉排序树
        return flag;

    //判断左节点及其所有子节点是否比其小
    if (T->lchild->data.key <= T->data.key)
    {
        if (T->lchild->lchild->data.key <= T->lchild->data.key)
        {
            if (!flag)
                return flag;
            else
            {
                T->lchild->data = T->data;
                return JudgeBiTree(T->lchild);
            }
        }
        else
            flag = FALSE;
    }
    else
        flag = FALSE;
    //判断右节点及其所有子节点是否比其大
    if (T->rchild->data.key >= T->data.key)
    {
        if (T->rchild->lchild->data.key >= T->lchild->data.key)
        {
            if (!flag)
                return flag;
            else
            {
                T->rchild->data = T->data;
                return JudgeBiTree(T->rchild);
            }
        }
        else
            flag = FALSE;
    }
    else
        flag = FALSE;
    return flag;
    /********** End **********/
}