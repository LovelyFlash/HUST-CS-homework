#include <bits/stdc++.h>
using namespace std;

int depth = 0, width = 0, dis = 0, tem_depth = 0, tem_width = 1, u, v, n;
struct Tree
{
    int num;
    Tree *right, *left, *father;
};

int search_node(Tree *root)
{
    int res = 0;
    if (root->left && root->left->num != v)
        res += 1 + search_node(root->left);
    else if (root->left)
        return 1;
    if (root->right && root->right->num != v)
        res += 1 + search_node(root->right);
    else if (root->right)
        return 1;
    if (res <= 1)
        res--;
    return res;
}

Tree *init_tree(int n)
{
    Tree *t = new Tree[n];
    memset(t, 0, sizeof(Tree) * n);
    for (int i = 0; i < n; i++)
    {
        t[i].num = i + 1;
        t[i].left = nullptr;
        t[i].right = nullptr;
        t[i].father = nullptr;
    }
    return t;
}

void create_tree(Tree *root, int n)
{
    int x, y;
    for (int i = 1; i < n; i++)
    {
        cin >> x >> y;
        if (root[x - 1].left == nullptr)
        {
            root[x - 1].left = &root[y - 1];
            root[y - 1].father = &root[x - 1];
        }
        else
        {
            root[x - 1].right = &root[y - 1];
            root[y - 1].father = &root[x - 1];
        }
    }
}

void search_depth(Tree *root)
{
    if (root->left)
    {
        tem_depth++;
        
        if (tem_depth > depth)
            depth = tem_depth;
        search_depth(root->left);
    }
    if (root->right)
    {
        tem_depth++;
        if (tem_depth > depth)
            depth = tem_depth;
        search_depth(root->right);
    }
    tem_depth--;
    return;
}

void search_width(Tree *root)
{
    int tem = 0;
    queue<Tree *> q;
    q.push(root);
    while (!q.empty())
    {
        if (width < tem_width)
            width = tem_width;
        while (tem_width--)
        {
            Tree *tem_node = q.front();
            q.pop();
            if (tem_node->left)
            {
                q.push(tem_node->left);
                tem++;
            }
            if (tem_node->right)
            {
                q.push(tem_node->right);
                tem++;
            }
        }
        tem_width = tem;
        tem = 0;
    }
}

int search_distance(Tree *root)
{
    dis = search_node(root);
    if (dis < 0)
        return 2 + search_distance(root->father);
    else
        return dis;
}

int main()
{
    cin >> n;
    Tree *root = init_tree(n);
    create_tree(root, n);
    search_depth(root);
    search_width(root);
    cin >> u >> v;
    cout << depth + 1 << endl
         << width << endl
         << search_distance(&root[u - 1]);
    return 0;
}