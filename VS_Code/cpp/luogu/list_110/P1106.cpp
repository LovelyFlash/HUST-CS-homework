#include <bits/stdc++.h>

using namespace std;

int main()
{
    int k;
    map<char, vector<int>> mp;
    string n;
    cin >> n;
    for (int i = 0; i < n.length(); i++)
        mp[n[i]].push_back(i);
    int n0=mp['0'].size();
    if(n0)
        while((mp['0'].back()-n0)<=k)
    return 0;
}