#include <bits/stdc++.h>
using INT = int;
#define int unsigned long long
#define ull unsigned long long
using namespace std;
inline ull read(){
    char c;
    ull x=0;
    while((c=getchar())==' '||c=='\n');
    do{
        x=x*10+c-'0';
    }while((c=getchar())>='0'&&c<='9');
    return x;
}
INT main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    // scanf("%llu", &n);
    n=read();
    // priority_queue<int, vector<int>, std::greater<int>> pq;
    // int a[n];
    list<int> a;
    while (n--)
    {
        a.push_back(read());
    };
    
    // sort(a.begin(),a.end());
    a.sort();
    int ans = 0;
    // while (!pq.empty())
    // {
    //     int a, b;
    //     a = pq.top();
    //     pq.pop();
    //     if (pq.empty())
    //     {
    //         if (ans == 0)
    //             ans = a;
    //         break;
    //     }
    //     b = pq.top();
    //     pq.pop();
    //     int c = a + b;
    //     ans += c;
    //     pq.push(c);
    // }
    while(a.size()>1){
        int c=a.front()+(a.pop_front(),a.front());
        a.pop_front();
        ans+=c;
        auto it=a.begin();
        while(it!=a.end()&&*it<c) it++;
        a.insert(--it,c);
    }
    if(ans==0&&!a.empty()) ans=a.front();
    printf("%llu", ans);
    return 0;

}