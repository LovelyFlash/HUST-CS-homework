#include <stack>

status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
// 先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL)
        return ERROR;

    std::stack<BiTree> s;
    s.push(T);

    while (!s.empty())
    {
        BiTree node = s.top();
        s.pop();
        visit(node);

        if (node->rchild)
            s.push(node->rchild);
        if (node->lchild)
            s.push(node->lchild);
    }

    return OK;
    /********** End **********/
}