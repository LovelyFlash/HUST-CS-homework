#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define MAXLEN 20001

int main()
{
    ull weight, max_weight[MAXLEN] = {0};
    long count = 0, mode, n;
    cin >> n;
    while (n--)
    {
        cin >> mode;
        switch (mode)
        {
        case 0:
            cin >> weight;
            count++;
            max_weight[count] = max(max_weight[count - 1], weight);
            break;
        case 1:
            if (count)
                count--;
            break;
        case 2:
            cout << max_weight[count] << endl;
            break;
        }
    }
    return 0;
}