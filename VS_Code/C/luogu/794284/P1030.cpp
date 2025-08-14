#include <bits/stdc++.h>
using namespace std;

struct Tree
{
    char data;
    Tree *left, *right;
};

void find_tree(string middle, string end)
{
    if (middle.empty() || end.empty())
        return;

    Tree *root = new Tree;
    root->data = end.back();
    end.pop_back();

    cout << root->data;
    size_t pos = middle.find(root->data);
    if (pos != string::npos)
    {
        string left_middle = middle.substr(0, pos);
        string right_middle = middle.substr(pos + 1);
        string left_end = end.substr(0, pos);
        string right_end = end.substr(pos);

        root->left = new Tree;
        root->right = new Tree;

        find_tree(left_middle, left_end);
        find_tree(right_middle, right_end);
    }

    delete root;
}

int main()
{
    string middle, end;
    cin >> middle >> end;
    find_tree(middle, end);
    return 0;
}