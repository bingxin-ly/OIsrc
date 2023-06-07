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

const int N = 5e5 + 10;
char c[N];
vector<int> g[N];
vector<pair<int, int>> query[N];

int dep[N], siz[N], son[N];
void pre(int u, int f)
{
    dep[u] = dep[f] + 1, siz[u] = 1;
    for (auto v : g[u])
        if (v != f)
        {
            pre(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
}

bool ans[N];
int big, cnt[N][26];
void calc(int u, int f)
{
    cnt[dep[u]][c[u] - 'a'] ^= 1;
    for (auto v : g[u])
        if (v != f && v != big)
            calc(v, u);
}
bool check(const int s[])
{
    int ret = 0;
    for (int i = 0; i < 26; i++)
        ret += s[i];
    return ret <= 1;
}
void dsu(int u, int f, bool keep)
{
    for (auto v : g[u])
        if (v != f && v != son[u])
            dsu(v, u, false);
    if (son[u])
        dsu(son[u], u, true), big = son[u];

    calc(u, f);

    for (auto &i : query[u])
        ans[i.second] = check(cnt[i.first]);

    big = 0;
    if (!keep)
        calc(u, f);
}

signed main()
{
    int n = read(), m = read();
    for (int i = 2, u; i <= n; i++)
        u = read(), g[u].emplace_back(i), g[i].emplace_back(u);
    scanf("%s", c + 1);

    pre(1, 0);
    for (int i = 1, a, b; i <= m; i++)
        a = read(), b = read(), query[a].emplace_back(b, i);

    dsu(1, 0, true);
    for_each(ans + 1, ans + m + 1, [](auto x)
             { puts(x ? "Yes" : "No"); });
    return 0;
}