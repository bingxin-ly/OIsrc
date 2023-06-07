#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10, INF = 0x7fffffff;
int leaf[N];
vector<int> g[N];

inline int read()
{
    int o = 1, p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            o = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0',
        c = getchar();
    return o * p;
}

// 子树上值的合并
set<int> leaves[N];
int merge(set<int> &x, set<int> &y)
{
    if (x.size() < y.size())
        swap(x, y);
    int minn = INF;
    for (set<int>::iterator it = y.begin(), pre, suc; it != y.end(); it++)
    {
        pre = suc = x.lower_bound(*it);
        if (pre != x.begin())
            pre--;
        if (pre != x.end())
            minn = min(minn, abs(*it - *pre));
        if (suc != x.end())
            minn = min(minn, abs(*it - *suc));
        x.insert(*it);
    }
    return minn;
}
int ans[N];
void dfs(int u)
{
    ans[u] = INF;
    if (!g[u].size())
        return leaves[u].insert(leaf[u]), void();

    for (auto v : g[u])
    {
        dfs(v);
        ans[u] = min(ans[u], ans[v]);
        ans[u] = min(ans[u], merge(leaves[u], leaves[v]));
    }
}

signed main()
{
    int n(read()), m(read());
    for (int i = 2, p; i <= n; i++)
        p = read(), g[p].emplace_back(i);
    for (int i = n - m + 1; i <= n; i++)
        leaf[i] = read();

    dfs(1);

    for (int i = 1; i <= n - m; i++)
        cout << ans[i] << ' ';
    return 0;
}