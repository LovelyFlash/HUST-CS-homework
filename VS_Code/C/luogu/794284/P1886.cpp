#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<long> num(n);
    for (int i = 0; i < n; i++)
        cin >> num[i];

    deque<int> maxq, minq;
    vector<long> maxv, minv;
    for (int i = 0; i < n; i++)
    {
        // 维护最大值队列
        while (!maxq.empty() && num[maxq.back()] <= num[i])
            maxq.pop_back();
        maxq.push_back(i);
        if (maxq.front() <= i - k)
            maxq.pop_front();

        // 维护最小值队列
        while (!minq.empty() && num[minq.back()] >= num[i])
            minq.pop_back();
        minq.push_back(i);
        if (minq.front() <= i - k)
            minq.pop_front();

        // 记录结果
        if (i >= k - 1)
        {
            minv.push_back(num[minq.front()]);
            maxv.push_back(num[maxq.front()]);
        }
    }

    for (auto v : minv)
        cout << v << ' ';
    cout << endl;
    for (auto v : maxv)
        cout << v << ' ';
    return 0;
}