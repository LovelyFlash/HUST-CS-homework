#include <bits/stdc++.h>

using namespace std;

int main()
{
    string w1, w2;
    cin >> w1 >> w2;
    vector<int> ans;
    int j = 0;
    int flag = 0;
    for (int i = 0; i < (int)w2.length(); i++)
    {
        if (i)
            j = ans.back() + 1;
        while (j < w1.length() && w1[j++] != w2[i])
            ;
        if (j == w1.length() && flag == 0)
        {
            if (i == 0)
                ans.push_back(0);
            else
                ans.push_back(ans.back() + 1);
            ++flag;
        }
        else if (j == w1.length() && flag == 1)
            break;
        else
            ans.push_back(j - 1);
    }
    if (ans.size() == (int)w2.length())
        for (int i : ans)
            cout << i << ' ';
    else
        cout << "no_answer!";
}