#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e3 + 5;
int m;
vector<pair<int, int>> g[N];

int in[N], S[N];
void SPFA()
{
    queue<int> q;
    memset(S, ~0x3f, sizeof(S));
    q.emplace(0), S[0] = 0, in[0] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), in[u] = 0;
        for (const auto &[v, w] : g[u])
            if (S[v] < S[u] + w)
            {
                S[v] = S[u] + w;
                if (!in[v])
                    q.emplace(v), in[v] = 1;
            }
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> m;
    for (int i = 1, a, b, c; i <= m; i++)
        cin >> a >> b >> c, g[a].emplace_back(b + 1, c);
    for (int i = 0; i < 1002; i++)
        g[i].emplace_back(i + 1, 0), g[i + 1].emplace_back(i, -1);
    SPFA();
    cout << S[1002];
    return 0;
}