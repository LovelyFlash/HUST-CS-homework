#include <bits/stdc++.h>

using namespace std;

struct Time
{
public:
    int time;
    int num;
    Time(int t, int n) : time(t), num(n) {}
};

int main()
{
    vector<Time> time;
    int n, t;
    double res = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> t;
        Time tem(t, i);
        time.push_back(tem);
    }
    stable_sort(time.begin(), time.end(), [](const Time &a, const Time &b)
                { return a.time < b.time; });
    for (int i = 0; i < n; i++)
    {
        cout << time[i].num + 1 << ' ';
        res += (n - i - 1) * time[i].time;
    }

    cout << endl;
    printf("%.2lf", (double)res / n);
    return 0;
}