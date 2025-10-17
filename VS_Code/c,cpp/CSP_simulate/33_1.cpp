#include <bits/stdc++.h>

using namespace std;
int main()
{
    int x, y;
    cin >> x >> y;
    int article[y] = {0}, time[y] = {0}, length, num;
    bool flag[y];
    for (int i = 0; i < x; i++)
    {
        cin >> length;
        for (int j = 0; j < y; j++)
            flag[j] = false;
        for (int j = 0; j < length; j++)
        {
            cin >> num;
            if (!flag[num - 1])
            {
                article[num - 1]++;
                flag[num - 1] = true;
            }
            time[num - 1]++;
        }
    }
    for (int j = 0; j < y; j++)
        cout << article[j] << ' ' << time[j] << endl;
    return 0;
}
