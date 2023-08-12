#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;

constexpr int N = 1e5 + 5;
int n, m, k, c[N];
vector<pii> pos[N], neg[N];

long long ans, f[N], g[N];
int fr[N], to[N], vis[N];
void dijkstra(vector<pii> *g, ll *dis, int *frm)
{
    priority_queue<pli, vector<pli>, greater<>> q;
    memset(vis, 0, sizeof(vis)), memset(dis, 0x3f, N << 3);
    for (int i = 1; i <= k; i++)
        q.emplace(dis[c[i]] = 0, c[i]), frm[c[i]] = c[i];
    while (!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (const auto &[v, w] : g[u])
            if (dis[v] > dis[u] + w)
                q.emplace(dis[v] = dis[u] + w, v), frm[v] = frm[u];
    }
}
void solve()
{
    cin >> n >> m >> k, ans = LLONG_MAX;
    for (int i = 1; i <= n; i++)
        pos[i].clear(), neg[i].clear();
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w,
            pos[u].emplace_back(v, w), neg[v].emplace_back(u, w);
    for (int i = 1; i <= k; i++)
        cin >> c[i];

    dijkstra(pos, f, fr), dijkstra(neg, g, to);

    for (int u = 1; u <= n; u++)
        for (const auto &[v, w] : pos[u])
            if (fr[u] != to[v])
                ans = min(ans, f[u] + w + g[v]);
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