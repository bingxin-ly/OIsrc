#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
vector<int> graph[N];

int fa[N], dep[N], siz[N];          // normal
int son[N], top[N], dfn[N], rnk[N]; // decomposition

void dfs1(int o) // build
{
    son[o] = -1, siz[o] = 1;
    for (auto v : graph[o])
        if (!dep[v])
        {
            dep[v] = dep[o] + 1, fa[v] = o;
            dfs1(v);
            siz[o] += siz[v];
            if (son[o] == -1 || siz[v] > siz[son[o]])
                son[o] = v;
        }
}

int cnt;
void dfs2(int o, int t) // decomposition
{
    top[o] = t, cnt++;
    dfn[o] = cnt, rnk[cnt] = o;
    if (son[o] == -1)
        return;
    dfs2(son[o], t);
    for (auto v : graph[o])
        if (v != son[o] && v != fa[o])
            dfs2(v, v);
}

int lca(int u, int v)
{
    while (top[u] != top[v])
        if (dep[top[u]] > dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    return dep[u] > dep[v] ? v : u;
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    dep[s] = 1;
    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v,
            graph[u].push_back(v), graph[v].push_back(u);

    dfs1(s), dfs2(s, s);
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
    return 0;
}