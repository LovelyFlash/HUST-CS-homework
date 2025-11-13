#include <bits/stdc++.h>

using namespace std;

struct Exam
{
    int begin, end;
};

int main()
{
    vector<Exam> exams;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Exam t;
        cin >> t.begin >> t.end;
        exams.push_back(t);
    }

    int res = 1;
    sort(exams.begin(), exams.end(), [](const Exam &a, const Exam &b)
         { return a.end < b.end; });
    int lastExam = 0;
    for (int i = 1; i < n; i++)
    {
        if (exams[i].begin < exams[lastExam].end)
            continue;
        else
        {
            res++;
            lastExam = i;
        }
    }
    cout << res;
    return 0;
}