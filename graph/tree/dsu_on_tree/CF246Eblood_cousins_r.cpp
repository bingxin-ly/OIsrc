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
string name[N];
vector<pair<int, int>> querys[N];

int dep[N], siz[N], son[N];
void pre(int u)
{
    siz[u] = 1;
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
unordered_set<string> s[N];
void calc(int u, bool op)
{
    if (s[dep[u]].count(name[u]) ^ op)
        if (op)
            s[dep[u]].insert(name[u]), cnt[dep[u]]++;
        else
            s[dep[u]].erase(name[u]), cnt[dep[u]]--;
    for (auto v : g[u])
        if (v != heavy)
            calc(v, op);
}
void dsu(int u, bool keep)
{
    for (auto v : g[u])
        if (v != son[u])
            dsu(v, false);
    if (son[u])
        dsu(son[u], true), heavy = son[u];

    calc(u, true);
    for (auto i : querys[u])
        ans[i.second] = cnt[dep[u] + i.first];

    heavy = 0;
    if (!keep)
        calc(u, false);
}

char str[20];
signed main()
{
    int n(read());
    for (int i = 1, p; i <= n; i++)
    {
        scanf("%s", str);
        p = read();
        g[p].emplace_back(i), name[i] = str;
    }

    int m(read());
    for (int i = 1, u, k; i <= m; i++)
        u = read(), k = read(), querys[u].emplace_back(k, i);

    pre(0), dsu(0, true);

    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}