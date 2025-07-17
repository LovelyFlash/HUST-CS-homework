#include <bits/stdc++.h>
using namespace std;
stack<int> st;
int n, op, x, f[100005];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> op;
        if (op == 0)
        {
            scanf("%d", &x), st.push(x);
            f[st.size() - 1] = max(f[st.size() - 2], x);
        }
        if (op == 1 && !st.empty())
            st.pop();
        if (op == 2)
            cout << f[st.size() - 1] << endl;
    }
    return 0;
}
