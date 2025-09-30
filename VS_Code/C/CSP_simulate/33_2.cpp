#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
int main()
{
    int x, y;
    cin >> x >> y;
    string tem;
    ull word;
    set<ull> w1, w2;
    char c;
    for (int i = 0; i < x; i++)
    {
        cin >> tem;
        word = 0;
        for (int j = 0; j < tem.size(); j++)
        {
            c = tem[j];
            if (c > 'Z')
                c -= 32;
            word += (c - 'A') * pow(26, j);
        }
        w1.insert(word);
    }

    for (int i = 0; i < y; i++)
    {
        cin >> tem;
        word = 0;
        for (int j = 0; j < tem.size(); j++)
        {
            c = tem[j];
            if (c > 'Z')
                c -= 32;
            word += (c - 'A') * pow(26, j);
        }
        w2.insert(word);
    }

    int result = 0;
    for (int num : w1)
        if (w2.find(num) != w2.end())
            result++;

    cout << result << ' ' << w1.size() + w2.size() - result << endl;

    return 0;
}