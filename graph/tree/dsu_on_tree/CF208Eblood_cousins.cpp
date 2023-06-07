#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int N = 1e5 + 10;
vector<int> g[N];
vector<pair<int, int>> querys[N];

int dep[N], siz[N], son[N], fa[N][20];
int find_father(int x, int y)
{
    for (int i = 18; i >= 0; i--)
        if (y >= (1 << i))
            y -= (1 << i), x = fa[x][i];
    return x;
}
void pre(int u)
{
    siz[u] = 1;
    for (int i = 1; i <= 18; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto v : g[u])
    {
        dep[v] = dep[u] + 1;
        pre(v);
        siz[u] += siz[v];
        if (siz[v] >= siz[son[u]])
            son[u] = v;
    }
}

int heavy, cnt[N << 1], ans[N];
void calc(int u, int x)
{
    cnt[dep[u]] += x;
    for (auto v : g[u])
        if (v != heavy)
            calc(v, x);
}
void dsu(int u, bool keep)
{
    for (auto v : g[u])
        if (v != son[u])
            dsu(v, false);
    if (son[u])
        dsu(son[u], true), heavy = son[u];

    calc(u, 1);
    for (auto i : querys[u])
        ans[i.second] = cnt[dep[u] + i.first];

    heavy = 0;
    if (!keep)
        calc(u, -1);
}

signed main()
{
    int n(read());
    for (int i = 1, p; i <= n; i++)
        p = read(), fa[i][0] = p, g[p].emplace_back(i);
    for (int i = 1; i <= n; i++)
        if (!fa[i][0])
            pre(i);

    int m(read());
    for (int i = 1, u, k, e; i <= m; i++)
    {
        u = read(), k = read(), e = find_father(u, k);
        if (e)
            querys[e].emplace_back(k, i);
    }

    for (int i = 1; i <= n; i++)
        if (!fa[i][0])
            dsu(i, false);

    for (int i = 1; i <= m; i++)
        printf("%d ", ans[i] - 1 > 0 ? ans[i] - 1 : 0);
    return 0;
}