#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e3 + 5;
int n, m;
vector<pair<int, int>> g[N];

int in[N], dis[N], len[N];
void SPFA()
{
    queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    q.emplace(0), dis[0] = len[0] = 0, in[0] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), in[u] = 0;
        for (const auto &[v, w] : g[u])
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w, len[v] = len[u] + 1;
                if (len[u] == n)
                    cout << "NO", exit(0);
                q.emplace(v), in[v] = 1;
            }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, a, b, c; i <= m; i++)
        cin >> a >> b >> c, g[b].emplace_back(a, c);
    for (int i = 1; i <= n; i++)
        g[0].emplace_back(i, 0);
    SPFA();
    for (int i = 1; i <= n; i++)
        cout << dis[i] << ' ';
    return 0;
}