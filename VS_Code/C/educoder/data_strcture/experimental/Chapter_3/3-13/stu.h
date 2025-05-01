#include <bits/stdc++.h>

using namespace std;

status SaveBiTree(BiTree T, char FileName[])
// 将二叉树的结点数据写入到文件FileName中
{
    FILE *fp = fopen(FileName, "w");
    if (fp == NULL)
        return ERROR;

    stack<BiTree> s;
    s.push(T);

    while (!s.empty())
    {
        BiTree node = s.top();
        s.pop();
        if (node == NULL)
        {
            fprintf(fp, "-1 null\n"); // 空节点标志
        }
        else
        {
            fprintf(fp, "%d %s\n", node->data.key, node->data.others); // 写入节点数据
            s.push(node->rchild);
            s.push(node->lchild);
        }
    }

    fclose(fp);
    return OK;
}

status LoadBiTree(BiTree &T, char FileName[])
// 读入文件FileName的结点数据，创建二叉树
{
    FILE *fp = fopen(FileName, "r");
    if (fp == NULL)
        return ERROR;

    stack<BiTree *> s; // 栈用于存储父节点的指针
    T = NULL;          // 初始化二叉树为空
    s.push(&T);

    while (!s.empty())
    {
        BiTree *tem = s.top(); // 获取栈顶的父节点指针
        s.pop();

        int key;
        char others[100];
        if (fscanf(fp, "%d", &key) == EOF)
            break; // 文件读取结束

        if (key == -1)
        {
            fscanf(fp, "%s", others); // 跳过 "null"
            *tem = NULL;             // 空节点
            continue;
        }

        // 为新节点分配内存
        *tem = (BiTree)malloc(sizeof(BiTNode));
        if (*tem == NULL)
        {
            fclose(fp);
            return ERROR; // 内存分配失败
        }

        // 读取节点数据
        if (fscanf(fp, "%s", others) != 1)
        {
            fclose(fp);
            return ERROR; // 数据读取失败
        }
        (*tem)->data.key = key;
        strcpy((*tem)->data.others, others);
        (*tem)->lchild = NULL;
        (*tem)->rchild = NULL;

        // 将右子节点和左子节点的指针压入栈
        s.push(&((*tem)->rchild));
        s.push(&((*tem)->lchild));
    }

    fclose(fp);
    return OK;
}