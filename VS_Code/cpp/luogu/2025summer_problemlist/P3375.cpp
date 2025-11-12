#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string s)
{
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    string s = s2 + "#" + s1;
    int len = s.size(), len1 = s1.size(), len2 = s2.size();
    vector<int> lps = prefix_function(s), lps2 = prefix_function(s2);
    for (int i = len2 + 1; i < len; i++)
        if (lps[i] == len2)
            cout << i - len2 * 2 + 1 << endl;
    for (int i = 0; i < len2; i++)
        cout << lps2[i] << ' ';
    return 0;
}