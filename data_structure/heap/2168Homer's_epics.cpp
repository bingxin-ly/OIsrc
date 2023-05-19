#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

struct node
{
    int w, h;
    bool operator<(const node &o) const { return w == o.w ? h > o.h : w > o.w; }
};
priority_queue<node> q;
signed main()
{
    int n(read()), k(read());
    for (int i = 1; i <= n; i++)
        q.push({read(), 1});

    while ((q.size() - 1) % (k - 1))
        q.push({0, 1});

    int ans = 0;
    while (q.size() >= k)
    {
        int h = -1, w = 0;
        for (int i = 1; i <= k; i++)
        {
            node t = q.top();
            q.pop();
            h = max(h, t.h);
            w += t.w;
        }
        ans += w;
        q.push({w, h + 1});
    }
    printf("%lld\n%lld", ans, q.top().h - 1);
    return 0;
}
