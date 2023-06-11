#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
vector<pair<int, char>> graph[N];

int dep[N], siz[N], son[N], path[N];
void dfs1(int u) // build
{
    siz[u] = 1;
    for (auto i : graph[u])
    {
        int v = i.first;
        char c = i.second;
        dep[v] = dep[u] + 1, path[v] = path[u] ^ 1 << (c - 'a');
        dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}

#define V v.first
int mxsum, mx[1 << 22], ans[N];
void add(int u)
{
    for (int i = 0; i <= 22; i++)
    {
        int v = path[u] ^ (i < 22 ? 1 << i : 0);
        mxsum = max(mxsum, dep[u] + mx[v]);
    }
    for (auto v : graph[u])
        add(V);
}
void update(int u)
{
    mx[path[u]] = max(mx[path[u]], dep[u]);
    for (auto v : graph[u])
        update(V);
}
void del(int u)
{
    mx[path[u]] = ~0x3f3f3f3f;
    for (auto v : graph[u])
        del(V);
}
void dfs4(int u)
{
    for (auto v : graph[u])
        if (V != son[u])
            dfs4(V), del(V);

    if (son[u])
        dfs4(son[u]);
    mxsum = 2 * dep[u];
    for (int i = 0; i <= 22; i++)
    {
        int v = path[u] ^ (i < 22 ? 1 << i : 0);
        mxsum = max(mxsum, mx[v] + dep[u]);
    }
    mx[path[u]] = max(mx[path[u]], dep[u]);
    for (auto v : graph[u])
        if (V != son[u])
            add(V), update(V);
    ans[u] = mxsum - 2 * dep[u];
}

void dfs5(int u)
{
    for (auto v : graph[u])
        dfs5(V), ans[u] = max(ans[u], ans[V]);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 2, x; i <= n; i++)
    {
        char c;
        cin >> x >> c;
        graph[x].emplace_back(i, c);
    }

    dfs1(1);
    memset(mx, ~0x3f, sizeof(mx));
    dfs4(1), dfs5(1);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    return 0;
}