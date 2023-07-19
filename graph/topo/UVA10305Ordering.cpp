#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, m, in[N];
vector<int> g[N];

void solve()
{
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, g[u].emplace_back(v), in[v]++;
    // toposort
    queue<int> q;
    vector<int> s;
    for (int i = 1; i <= n; i++)
        if (!in[i])
            q.emplace(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), s.emplace_back(u);
        for (int v : g[u])
            if (--in[v] == 0)
                q.emplace(v);
    }
    for (int u : s)
        cout << u << ' ';
    cout << '\n';
}
void clear()
{
    memset(in, 0, sizeof(in));
    for (int i = 1; i <= n; i++)
        g[i].clear();
}
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
    #endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m)
        solve(), clear();
    return 0;
}