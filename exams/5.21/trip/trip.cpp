#include <bits/stdc++.h>
using namespace std;

const int M = 1e5 + 10, WINT = 15001;
vector<pair<int, double>> graph[M];
int tot, provi[M], road[M];
int s, t;

bool st[M];
bool check(int l, int r)
{
    memset(st, 0, sizeof(st));
    queue<int> q;
    q.push(s), st[s] = true;

    while (!q.empty())
    {
        auto u = q.front();
        q.pop();

        for (auto i : graph[u])
        {
            int v = i.first;
            if (st[v])
                continue;
            if (l <= i.second && i.second <= r)
                q.push(v), st[v] = true;
        }
    }
    return st[t];
}
signed main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w,
            graph[u].emplace_back(v, w),
            graph[v].emplace_back(u, w);

    for (int i = 1, k; i <= n; i++)
    {
        cin >> k, tot += k;
        for (int j = 1, c; j <= k; j++)
            cin >> c, road[c] = i;
    }

    for (int i = 1; i <= n; i++)
        cin >> provi[i];

    for (int i = 1; i <= tot; i++)
        for (auto &v : graph[i])
            v.second *= (provi[road[i]] + provi[road[v.first]]) / 200.0;

    cin >> s >> t;
    int l = 0, r = WINT, L, R;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid, WINT))
            l = mid + 1;
        else
            r = mid;
    }
    l -= 1, L = l, r = WINT;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(L, mid))
            r = mid;
        else
            l = mid + 1;
    }
    R = l;
    cout << L << ' ' << R;
    return 0;
}