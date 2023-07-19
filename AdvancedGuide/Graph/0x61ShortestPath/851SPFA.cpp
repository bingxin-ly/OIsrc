#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m;
vector<pair<int, int>> g[N];

int in[N], dis[N];
queue<int> q;
void SPFA(int s)
{
    memset(dis, 0x7f, sizeof(dis));
    q.emplace(s), dis[s] = 0, in[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), in[u] = false;
        for (const auto &[v, w] : g[u])
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if (!in[v])
                    q.emplace(v), in[v] = true;
            }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w);
    SPFA(1);
    if (dis[n] != 0x7f7f7f7f)
        cout << dis[n];
    else
        cout << "impossible";
    return 0;
}