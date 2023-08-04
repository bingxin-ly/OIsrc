#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e3 + 5;
int n, m;
vector<pair<int, int>> g[N];

int in[N], dis[N], len[N];
bool SPFA()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(in, 0, sizeof(in));
    queue<int> q;
    dis[1] = len[1] = 0, q.emplace(1), in[1] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), in[u] = 0;
        for (const auto &[v, w] : g[u])
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w, len[v] = len[u] + 1;
                if (len[v] == n)
                    return true;
                if (!in[v])
                    q.emplace(v), in[v] = 1;
            }
    }
    return false;
}
void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        g[i].clear();
    for (int i = 1, u, v, w; i <= m; i++)
    {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        if (w >= 0)
            g[v].emplace_back(u, w);
    }
    cout << (SPFA() ? "YES\n" : "NO\n");
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}