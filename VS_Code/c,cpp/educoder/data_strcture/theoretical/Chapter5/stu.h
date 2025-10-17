status JudgeBiTree(BiTree T)
// 判断二叉树T是否为二叉排序树
{
    /********** Begin *********/
    static BiTree prev = NULL; // 用于记录中序遍历的前一个节点

    if (T == NULL) {
        return OK; // 空树是二叉排序树
    }

    // 递归检查左子树
    if (!JudgeBiTree(T->lchild)) {
        return ERROR;
    }

    // 检查当前节点的 key 是否大于中序遍历的前一个节点的 key
    if (prev != NULL && T->data.key <= prev->data.key) {
        return ERROR;
    }
    prev = T; // 更新前一个节点

    // 递归检查右子树
    return JudgeBiTree(T->rchild);
    /********** End *********/
}