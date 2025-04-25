status Assign(BiTree &T, KeyType e, TElemType value)
// 实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 如果当前节点为空，返回 ERROR
    if (T == NULL)
        return ERROR;

    // 如果当前节点代号为 1（根节点）
    if (e == 1)
    {
        // 检查关键字是否唯一
        if (value.key != T->data.key)
            return ERROR;

        // 修改节点值
        T->data = value;
        return OK;
    }

    // 计算父节点代号
    int parent = e / 2;

    // 判断当前节点是左子节点还是右子节点
    if (e % 2 == 0) // 左子节点
    {
        if (Assign(T->lchild, parent, value) == OK)
            return OK;
    }
    else // 右子节点
    {
        if (Assign(T->rchild, parent, value) == OK)
            return OK;
    }

    // 如果未找到，返回 ERROR
    return ERROR;
}