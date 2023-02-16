#include <bits/stdc++.h>
using namespace std;

const int MAX = 110;
int head[MAX << 1], edge[MAX << 1], nxt[MAX << 1], cnt;
int n, w[MAX], sz[MAX];
ssize_t ans = LLONG_MAX, f[MAX];

void add(int u, int v)
{
    edge[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}
void pre(int u, int p, int dep)
{
    sz[u] = w[u];
    for (int i = head[u]; i; i = nxt[i])
        if (edge[i] != p)
            pre(edge[i], u, dep + 1), sz[u] += sz[edge[i]];
    f[1] += w[u] * dep;
}
void dp(int u, int p)
{
    for (int i = head[u]; i; i = nxt[i])
        if (edge[i] != p)
            f[edge[i]] = f[u] + sz[1] - sz[edge[i]] * 2, dp(edge[i], u);
    ans = min(ans, f[u]);
}

int main()
{
    cin >> n;
    int u, v;
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i] >> u >> v;
        if (u)
            add(i, u), add(u, i);
        if (v)
            add(i, v), add(v, i);
    }
    pre(1, 0, 0), dp(1, 0);
    cout << ans << endl;
    return 0;
}