#define max(x, y) ((x) > (y) ? (x) : (y))

int BiTreeDepth(BiTree T)
// 求二叉树T的深度
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int depth = 0;
    ;
    if (T == nullptr)
        return 0;
    else
    {
        int left = BiTreeDepth(T->lchild);
        int right = BiTreeDepth(T->rchild);
        depth = max(left, right) + 1;
    }
    return depth;
    /********** End **********/
}
