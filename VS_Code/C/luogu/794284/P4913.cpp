#include <bits/stdc++.h>
using namespace std;

int depth = 0, tem_depth = 0, n;
struct Tree
{
    int num;
    Tree *right, *left;
};

Tree *init_tree(int n)
{
    Tree *t = new Tree[n];
    memset(t, 0, sizeof(Tree) * n);
    for (int i = 0; i < n; i++)
    {
        t[i].num = i + 1;
        t[i].left = nullptr;
        t[i].right = nullptr;
    }
    return t;
}

void create_tree(Tree *root, int n)
{
    int x, y;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        if (x)
            root[i].left = &root[x - 1];
        if (y)
            root[i].right = &root[y - 1];
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

int main()
{
    cin >> n;
    Tree *root = init_tree(n);
    create_tree(root, n);
    search_depth(root);
    cout << depth + 1 << endl;
    return 0;
}