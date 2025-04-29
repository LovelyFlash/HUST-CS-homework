#include <stack>

status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
// 后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL)
        return ERROR;

    std::stack<BiTree> s1, s2; // 定义两个栈
    s1.push(T);                // 将根节点压入第一个栈

    // 使用第一个栈进行遍历
    while (!s1.empty())
    {
        BiTree node = s1.top();
        s1.pop();
        s2.push(node); // 将节点压入第二个栈

        // 先将左子节点压入第一个栈，再将右子节点压入第一个栈
        if (node->lchild)
            s1.push(node->lchild);
        if (node->rchild)
            s1.push(node->rchild);
    }

    // 从第二个栈中依次弹出节点并访问
    while (!s2.empty())
    {
        BiTree node = s2.top();
        s2.pop();
        visit(node);
    }

    return OK;
/********** End **********/
}
