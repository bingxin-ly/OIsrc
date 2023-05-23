// Statistical Color, an easy aplication for dsu on tree
// inventor of the dsu on tree's blog https://codeforces.com/blog/entry/44351
// other blog https://codeforces.com/blog/entry/67696
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
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

const int N = 1e5 + 10;
int col[N], query[N];
vector<int> g[N];

int son[N], siz[N];
void dfs1(int u, int p)
{
    son[u] = -1, siz[u] = 1;
    for (auto v : g[u])
        if (v != p)
        {
            dfs1(v, u);
            siz[u] += siz[v];
            if (son[u] == -1 || siz[v] > siz[son[u]])
                son[u] = v;
        }
}

bool cnt[N];
vector<int> vec[N];
void dfs2(int u, int p, bool keep)
{
    for (auto v : g[u])
        if (v != p && v != son[u])
            dfs2(v, u, false);

    if (son[u] != -1)
        dfs2(son[u], u, true), swap(vec[u], vec[son[u]]);
    vec[u].emplace_back(u);
    cnt[col[u]] = true;
    for (auto v : g[u])
        if (v != p && v != son[u])
            for (auto x : vec[v])
                cnt[col[x]] = true, vec[u].emplace_back(x);

    // answer the query
    unordered_set<int> ans;
    for (auto v : vec[u])
        ans.insert(col[v]);
    query[u] = ans.size();

    if (!keep)
        for (auto v : vec[u])
            cnt[col[v]] = false;
}

signed main()
{
    int n = read();
    for (int i = 1, u, v; i < n; i++)
        u = read(), v = read(), g[u].emplace_back(v), g[v].emplace_back(u);
    for (int i = 1; i <= n; i++)
        col[i] = read();

    dfs1(1, 0), dfs2(1, 0, true);

    int m = read();
    for (int i = 1; i <= m; i++)
        write(query[read()]), putchar('\n');
    return 0;
}