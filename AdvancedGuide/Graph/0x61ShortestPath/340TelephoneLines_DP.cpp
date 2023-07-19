// 借助 SPFA 迭代 DP 写法：queue队列里不记几条电缆免费，更新状态时直接用 for 循环
// 由于常数小，导致反而比分层图写法要快（开 O2 也一样）
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
int n, m, k;
vector<pair<int, int>> g[N];

int f[N][N], in[N];
queue<int> q;
void SPFA()
{
    memset(f, 0x3f, sizeof(f));
    q.emplace(1), in[1] = true, f[1][0] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), in[u] = false;
        for (const auto &[v, w] : g[u])
        {
            for (int p = 0; p <= k; p++)
                if (f[v][p] > max(f[u][p], w))
                {
                    f[v][p] = max(f[u][p], w);
                    if (!in[v])
                        q.emplace(v), in[v] = true;
                }
            for (int p = 0; p < k; p++)
                if (f[v][p + 1] > f[u][p])
                {
                    f[v][p + 1] = f[u][p];
                    if (!in[v])
                        q.emplace(v), in[v] = true;
                }
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    SPFA();
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= k; i++)
        ans = min(ans, f[n][i]);
    cout << (ans != 0x3f3f3f3f ? ans : -1);
    return 0;
}