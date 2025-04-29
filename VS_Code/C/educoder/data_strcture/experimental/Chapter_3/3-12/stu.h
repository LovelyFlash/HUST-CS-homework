#include <bits/stdc++.h>

using namespace std;
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
// 按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL)
        return ERROR;

    queue<BiTree> q;
    q.push(T);
    while (!q.empty())
    {
        BiTree node = q.front();
        q.pop();
        visit(node);
        if (node->lchild != nullptr)
            q.push(node->lchild);
        if (node->rchild != nullptr)
            q.push(node->rchild);
    }
    return OK;
    /********** End **********/
}