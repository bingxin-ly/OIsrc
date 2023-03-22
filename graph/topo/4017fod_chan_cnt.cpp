#include <bits/stdc++.h>
using namespace std;

const int MOD = 80112002;
const int MAXN = 5e3 + 10, MAXM = 5e5 + 10;

int n, m, ans;
int in[MAXN], out[MAXN], f[MAXN];
queue<int> q;
struct edge
{
    int to, w;
};
vector<edge> graph[MAXN];

inline void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}

void toposort()
{
    for (int i = 1; i <= n; i++)
        if (!in[i])
            f[i] = 1, q.push(i);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto i : graph[u])
        {
            int v = i.to;
            f[v] += f[u];
            f[v] %= MOD;
            if (!--in[v])
                if (!out[v])
                    ans += f[v], ans %= MOD;
                else
                    q.push(v);
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        add(u, v);
        out[u]++, in[v]++;
    }
    toposort();
    cout << ans;
    return 0;
}
