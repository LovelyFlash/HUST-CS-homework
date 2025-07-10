#include <bits/stdc++.h>

typedef struct line
{
    int *num;
    line *next;
    line *prev;
} Line;
using namespace std;

int input(Line *l, int n)
{
    int head = 0, tail = 0;
    l[0].num = new int(1);
    l[0].next = nullptr;
    l[0].prev = nullptr;
    for (int i = 1; i < n; i++)
    {
        int k, p;
        cin >> k >> p;
        k--;
        l[i].num = new int(i + 1);
        if (!p)
        {
            l[i].next = &l[k];
            l[i].prev = l[k].prev;
            if (l[k].prev != nullptr)
                l[k].prev->next = &l[i];
            l[k].prev = &l[i];
            if (k == head)
                head = i;
        }
        else
        {
            l[i].prev = &l[k];
            l[i].next = l[k].next;
            if (l[k].next != nullptr)
                l[k].next->prev = &l[i];
            l[k].next = &l[i];
            if (k == tail)
                tail = i;
        }
    }
    return head;
}
void del(Line *l, int &head, int m, int n)
{
    vector<bool> removed(n, false);
    for (int i = 0; i < m; i++)
    {
        int delIndex;
        cin >> delIndex;
        delIndex--;
        if (removed[delIndex])
            continue;
        removed[delIndex] = true;
        if (l[delIndex].prev != nullptr)
            l[delIndex].prev->next = l[delIndex].next;
        if (l[delIndex].next != nullptr)
            l[delIndex].next->prev = l[delIndex].prev;
        if (head == delIndex)
        {
            // 更新head为下一个未被删除的节点
            int next = l[delIndex].next ? (l[delIndex].next - l) : -1;
            while (next != -1 && removed[next])
                next = l[next].next ? (l[next].next - l) : -1;
            head = next;
        }
    }
}

void output(Line *l, int head, int n)
{
    Line *p = &l[head];
    while (p != nullptr)
    {
        cout << *(p->num) << " ";
        p = p->next;
    }
}

int main()
{
    int n, head = 0;
    cin >> n;
    Line l[n];
    head = input(l, n);
    int m;
    cin >> m;
    del(l, head, m, n);
    output(l, head, n);
    return 0;
}