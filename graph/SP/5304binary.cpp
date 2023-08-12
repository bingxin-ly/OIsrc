#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pli = pair<ll, int>;

constexpr int N = 1e5 + 5;
int n, m, k, c[N], t[N];
vector<pair<int, int>> g[N];

ll ans, dis[N];
priority_queue<pli, vector<pli>, greater<>> q;
ll dijkstra()
{
    static bool vis[N];
    memset(vis, 0, sizeof(vis));
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u]) // 换成 AlexWei 的写法常数可以更小
            continue;
        vis[u] = true;
        if (t[u])
            return dis[u];
        for (const auto &[v, w] : g[u])
            if (dis[v] > dis[u] + w)
                q.emplace(dis[v] = dis[u] + w, v);
    }
    return LLONG_MAX;
}
void solve()
{
    cin >> n >> m >> k, ans = LLONG_MAX;
    memset(t, 0, sizeof(t));
    for (int i = 1; i <= n; i++)
        g[i].clear();
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w);
    for (int i = 0; i < k; i++)
        cin >> c[i];

    for (int p = 0; p <= __lg(k); p++)
    {
        memset(dis, 0x3f, sizeof(dis));
        for (int i = 0; i < k; i++)
            if (i >> p & 1)
                q.emplace(dis[c[i]] = 0, c[i]), t[c[i]] = 0;
            else
                t[c[i]] = 1;
        ans = min(ans, dijkstra());

        memset(dis, 0x3f, sizeof(dis));
        for (int i = 0; i < k; i++)
            if (!(i >> p & 1))
                q.emplace(dis[c[i]] = 0, c[i]), t[c[i]] = 0;
            else
                t[c[i]] = 1;
        ans = min(ans, dijkstra());
    }
    cout << ans << '\n';
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