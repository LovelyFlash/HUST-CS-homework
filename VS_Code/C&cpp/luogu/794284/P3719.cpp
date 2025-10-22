#include <bits/stdc++.h>
using namespace std;

int max_length(int length)
{
    char c;
    while (cin >> c)
    {
        if (c == 'a')
            length++;
        if (c == '(')
            length = length + max_length(0);
        if (c == '|')
            return max(length, max_length(0));
        if (c == ')')
            return length;
    }
    return length;
}
int main()
{
    cout << max_length(0);
    return 0;
}
