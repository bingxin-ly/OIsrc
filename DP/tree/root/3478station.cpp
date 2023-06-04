#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 10;
int n;
vector<int> tr[N];

int dep[N], siz[N], f[N];
void dfs1(int u, int fa)
{
    dep[u] = dep[fa] + 1, siz[u] = 1;
    for (auto v : tr[u])
        if (v != fa)
        {
            dfs1(v, u);
            siz[u] += siz[v];
            f[u] = f[v] + dep[u] * siz[v]; // 在里面统计
        }
}
int rt, ans;
void dfs2(int u, int fa)
{
    if (f[u] > ans)
        ans = f[u], rt = u;
    for (auto v : tr[u])
        if (v != fa)
        {
            f[v] = f[u] - siz[v] + n - siz[v];
            dfs2(v, u);
        }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v,
            tr[u].emplace_back(v), tr[v].emplace_back(u);

    dfs1(1, 0);
    /* for (int i = 1; i <= n; i++) // 也可以在外面统计
        f[1] += dep[i]; */
    dfs2(1, 0);
    cout << rt;
    return 0;
}