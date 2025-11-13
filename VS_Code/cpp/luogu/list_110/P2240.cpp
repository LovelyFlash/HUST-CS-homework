#include <bits/stdc++.h>

using namespace std;

class treasure
{
public:
    int mass, value;
    float vpm;
    treasure(int m, int v) : mass(m), value(v), vpm((float)value / (float)mass) {}
};

int main()
{
    int n, t, m, v;
    float res = 0;
    cin >> n >> t;
    vector<treasure> a;
    for (int i = 0; i < n; i++)
    {
        cin >> m >> v;
        treasure tem(m, v);
        a.push_back(tem);
    }
    sort(a.begin(), a.end(), [](const treasure &a, const treasure &b)
         { return a.vpm > b.vpm; });
    for (int i = 0; i < n; i++)
    {
        if (t >= a[i].mass)
        {
            res += a[i].value;
            t -= a[i].mass;
        }
        else
        {
            res += (float)((float)t * a[i].vpm);
            break;
        }
    }
    printf("%0.2f", res);
    return 0;
}