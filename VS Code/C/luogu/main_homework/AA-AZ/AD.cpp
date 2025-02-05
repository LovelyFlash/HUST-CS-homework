#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> vec(n + 1, vector<int>(m));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> vec[i][j];
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        int ans = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (i == j)
                continue;
            bool valid = true;
            for (int k = 0; k < m; ++k)
            {
                if (vec[j][k] <= vec[i][k])
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                ans = j;
                break;
            }
        }
        cout << ans << endl;
    }

    return 0;
}