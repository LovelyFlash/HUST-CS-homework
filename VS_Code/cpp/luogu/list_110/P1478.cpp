#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, s, a, b, x, y, ans = 0;
    cin >> n >> s >> a >> b;
    int h = a + b;
    vector<int> app;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        if (x <= h)
            app.push_back(y);
    }
    sort(app.begin(), app.end(), greater<int>());
    while (!app.empty())
    {

        if (s >= app.back())
        {
            s -= app.back();
            app.pop_back();
            ++ans;
        }

        else
            break;
    }
    cout << ans;
    return 0;
}