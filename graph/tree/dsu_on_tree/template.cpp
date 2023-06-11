// Statistical Color, an easy aplication for dsu on tree
// inventor of the dsu on tree's blog: https://codeforces.com/blog/entry/44351
// other blog: https://codeforces.com/blog/entry/67696
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
int col[N], ans[N];
vector<int> g[N];

int son[N], siz[N];
void dfs1(int u, int p)
{
    siz[u] = 1;
    for (auto v : g[u])
        if (v != p)
        {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
}

// implemented by STL vector
bool cntc[N];
vector<int> sub[N];
void dfs2(int u, int p, bool keep)
{
    for (auto v : g[u])
        if (v != p && v != son[u])
            dfs2(v, u, false);

    if (son[u])
        dfs2(son[u], u, true), swap(sub[u], sub[son[u]]);
    sub[u].emplace_back(u);

    cntc[col[u]] = true;
    for (auto v : g[u])
        if (v != p && v != son[u])
            for (auto x : sub[v])
                cntc[col[x]] = true, sub[u].emplace_back(x);

    // answer the ans
    unordered_set<int> s;
    for (auto v : sub[u])
        s.insert(col[v]);
    ans[u] = s.size();

    if (!keep)
        for (auto v : sub[u])
            cntc[col[v]] = false;
}

int big, sum, cnt[N];
void calc(int u, int p, int x)
{
    if (!cnt[col[u]])
        sum++;
    cnt[col[u]]++;
    for (auto v : g[u])
        if (v != p && v != big)
            calc(v, u, x);
}
void dsu(int u, int p, bool keep)
{
    for (auto v : g[u])
        if (v != p && v != son[u])
            dsu(v, u, false);
    if (son[u])
        dsu(son[u], u, true), big = son[u];

    calc(u, p, 1);

    ans[u] = sum;

    big = 0;
    if (!keep)
        calc(u, p, -1), sum = 0;
}

signed main()
{
    int n = read();
    for (int i = 1, u, v; i < n; i++)
        u = read(), v = read(), g[u].emplace_back(v), g[v].emplace_back(u);
    for_each(col + 1, col + n + 1, [](int &x)
             { x = read(); });

    dfs1(1, 0), dfs2(1, 0, true);

    int m = read();
    for (int i = 1; i <= m; i++)
        write(ans[read()]), putchar('\n');
    return 0;
}