#include<stack>

status InOrderTraverse(BiTree T, void (*visit)(BiTree))
// 中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL)
        return ERROR;

    std::stack<BiTree> s;
    BiTree current = T;   // 从根节点开始遍历

    while (current != NULL || !s.empty())
    {
        // 一直向左走，将沿途的节点压入栈
        while (current != NULL)
        {
            s.push(current);
            current = current->lchild;
        }

        // 栈顶节点出栈并访问
        current = s.top();
        s.pop();
        visit(current);

        // 转向右子树
        current = current->rchild;
    }

    return OK;
    /********** End **********/
}
