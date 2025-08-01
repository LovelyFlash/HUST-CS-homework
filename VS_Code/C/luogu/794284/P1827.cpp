#include <bits/stdc++.h>
using namespace std;
string front, middle;

void create_tree(string m, string f)
{
    if (f.empty())
        return;
    char root = f[0];
    int i = m.find(root);
    f.erase(f.begin());

    create_tree(m.substr(0, i), f.substr(0, i));
    create_tree(m.substr(i + 1), f.substr(i));

    cout << root;
}

int main()
{
    cin >> middle >> front;
    create_tree(middle, front);
    return 0;
}