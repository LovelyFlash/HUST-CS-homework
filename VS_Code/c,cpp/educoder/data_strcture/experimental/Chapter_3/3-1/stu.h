status CreateBiTree(BiTree &T, TElemType definition[])
/* 根据带空枝的二叉树先根遍历序列 definition 构造一棵二叉树，将根节点指针赋值给 T 并返回 OK，
   如果有相同的关键字，返回 ERROR。此题允许通过增加其它函数辅助实现本关任务 */
{
    static int index = 0; // 静态变量，用于记录当前处理的节点位置

    // 如果当前节点的 key 为 -1，表示空节点
    if (definition[index].key == -1)
    {
        // 递归结束条件，返回 NULL
        T = NULL;
        index++;
        return OK;
    }
    if (definition[index].key == 0)
    {
        T = NULL;
        index++;
        return OK;
    }

    // 创建新节点
    T = (BiTree)malloc(sizeof(BiTNode));
    if (!T)
    {
        exit(OVERFLOW);
    }

    // 赋值节点数据
    T->data = definition[index];

    // 检查关键字是否唯一
    for (int i = 0; i < index; i++)
    {
        if (definition[i].key == definition[index].key)
        {
            return ERROR;
        }
    }

    index++;

    // 递归创建左子树和右子树
    if (CreateBiTree(T->lchild, definition) == ERROR)
        return ERROR;
    else
    {
        if (CreateBiTree(T->rchild, definition) == ERROR)
            return ERROR;
        else 
            return OK;
    }
}