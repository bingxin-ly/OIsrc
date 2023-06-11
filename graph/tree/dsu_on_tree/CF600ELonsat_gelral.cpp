#include <bits/stdc++.h>
#define int long long
using namespace std;
inline void read(int &p)
{
    p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
}

const int N = 1e5 + 10;
vector<int> g[N];
int siz[N], son[N];

void pre(int u, int p)
{
    siz[u] = 1;
    for (auto v : g[u])
        if (v != p)
        {
            pre(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
}

int n, mx, sum, heavy;
int col[N], cnt[N], ans[N];
void add(int u, int p, int x)
{
    // 维护答案
    cnt[col[u]] += x;
    if (cnt[col[u]] > mx)
        mx = cnt[col[u]], sum = col[u];
    else if (cnt[col[u]] == mx)
        sum += col[u];
    for (auto v : g[u])
        if (v != p && v != heavy)
            add(v, u, x);
}
void dfs(int u, int p, bool keep)
{
    for (auto v : g[u])
        if (v != p && v != son[u])
            dfs(v, u, false);

    if (son[u])
        dfs(son[u], u, true), heavy = son[u];

    add(u, p, 1);

    // answer
    ans[u] = sum;

    heavy = 0;
    if (!keep)
        add(u, p, -1), sum = mx = 0;
}

signed main()
{
    read(n);
    for_each(col + 1, col + n + 1, [](int &x)
             { read(x); });
    for (int i = 1, u, v; i < n; i++)
        read(u), read(v),
            g[u].emplace_back(v), g[v].emplace_back(u);

    pre(1, 0), dfs(1, 0, true);

    for_each(ans + 1, ans + n + 1, [](int x)
             { printf("%lld ", x); });
    return 0;
}
