#include <bits/stdc++.h>
using namespace std;
const int mod = 10000;
int curnum, sum, t;
char c;
int main()
{
    scanf("%d", &t);
    while (scanf("%c", &c) && c != '\n')
    {
        scanf("%d", &curnum);
        if (c == '*')
            t = t * curnum % mod;
        else
            sum = (sum + t) % mod, t = curnum;
    }
    cout << (sum + t) % mod;
    return 0;
}