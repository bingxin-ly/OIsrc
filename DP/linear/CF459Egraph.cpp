#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int f[N], g[N];
struct
{
    int u, v, w;
} e[N];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, ans = 0;
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++)
        cin >> u >> v >> w, e[i] = {u, v, w};
    sort(e + 1, e + m + 1, [](const auto &a, const auto &b)
         { return a.w < b.w; });

    for (int i = 1, j; i <= m; i = j)
    {
        j = i + 1;
        while (e[j].w == e[i].w)
            j++;
        for (int k = i; k < j; k++)
            g[e[k].u] = f[e[k].u], g[e[k].v] = f[e[k].v];
        for (int k = i; k < j; k++)
            f[e[k].v] = max(f[e[k].v], g[e[k].u] + 1);
    }

    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i]);
    cout << ans;
    return 0;
}