// 添加 free0 函数的声明
void free0(void *p);

status ClearBiTree(BiTree &T)
// 将二叉树设置成空，并删除所有结点，释放结点空间
{
    if (T == NULL)
        return 0;
    ClearBiTree(T->lchild); // 递归清空左子树
    ClearBiTree(T->rchild); // 递归清空右子树
    free0(T);               // 使用自定义的 free0 函数释放节点
    T = NULL;               // 将指针置为空
    return 1;
}