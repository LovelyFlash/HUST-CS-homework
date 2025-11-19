#include <bits/stdc++.h>

using namespace std;

int main()
{
    int k;
    map<char, vector<int>> mp;
    string n;
    cin >> n >> k;
    for (int i = 0; i < n.length(); i++)
        mp[n[i]].push_back(i);
    int n0 = mp['0'].size();
    if (n0)
    {
        while ((mp['0'].back() - n0 + 1) >= k)
            mp['0'].pop_back();
        n.erase(n.begin(), n.begin() + mp['0'].back());
        k -= mp['0'].back() + 1;
    }
    for (int i = 9; i >= 0 && k > 0; i--)
        while (!mp[i + '0'].empty() && k > 0)
        {
            n.erase(n.begin() + mp[i + '0'].back());
            mp[i + '0'].pop_back();
            k--;
        }
    cout << n;
    return 0;
}