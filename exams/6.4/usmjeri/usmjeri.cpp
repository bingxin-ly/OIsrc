#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 10, MOD = 1e9 + 7;
pair<int, int> tr[N], p[N];

void add(int u, int v)
{
    if (!tr[u].first)
        tr[u].first = v;
    else
        tr[u].second = v;
}

int dep[N], son[N];
void dfs(int u, int f)
{
    son[f] = u;
    if (!u)
        return;
    dep[u] = dep[f] + 1;
    dfs(tr[u].first != f ? tr[u].first : tr[u].second, u);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++)
    {
        cin >> u >> v;
        if ((tr[u].first && tr[u].second) || (tr[v].first && tr[v].second))
            return cout << 0, 0;
        else
            add(u, v), add(v, u);
    }
    int rt = 1;
    while (tr[rt].first && tr[rt].second)
        rt = tr[rt].first;
    dfs(rt, 0);

    for (int i = 1; i <= m; i++)
        cin >> p[i].first >> p[i].second;
    sort(p + 1, p + m + 1, [](const auto a, const auto b)
         { return dep[a.first] < dep[b.first]; });

    for (int i = 1; i <= m; i++)
    {
        son[p[i].first] = p[i].second;
        if (dep[p[i].first] < dep[p[i - 1].second])
            son[p[i - 1].first] = p[i].second;
    }

    /* for (int i = 1; i <= n; i++)
        cout << son[i] << ' ';
    cout << endl; */

    int cnt = 0;
    while (son[rt])
        cnt++, rt = son[rt];

    int ans = 1;
    while (cnt > 30)
        (ans <<= 30) %= MOD, cnt -= 30;
    (ans <<= cnt) %= MOD;
    cout << ans;
    return 0;
}