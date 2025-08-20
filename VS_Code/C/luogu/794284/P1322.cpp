#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long

int dg()
{
    string s;
    char c;
    int rep, result = 0, tem;
    while (cin >> c)
    {
        if (c == ']')
            break;
        cin >> s >> rep;
        if (c == 'R')
        {
            tem = getchar();
            result += rep * dg();
            tem = getchar();
        }
        if (c == 'B')
            tem = getchar(), result -= rep;
        if (c == 'F')
            tem = getchar(), result += rep;
        if (tem == int(']'))
            break;
    }
    return result;
}
int main()
{
    cout << abs(dg());
    return 0;
}