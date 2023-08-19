#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 5;
int n, m, q, w[N], r[N], g[N];
mt19937 rng(time(0)); // random number generator
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        w[i] = rng();
    int sum = accumulate(w + 1, w + n + 1, 0), cur = 0;
    for (int i = 1, u, v; i <= m; i++)
        cin >> u >> v, r[v] += w[u], g[v] = r[v], cur += w[u];
    cin >> q;
    for (int t, u, v; q--;)
    {
        cin >> t;
        switch (t)
        {
        case 1:
            cin >> u >> v;
            r[v] -= w[u], cur -= w[u];
            break;
        case 2:
            cin >> v;
            cur -= r[v], r[v] = 0;
            break;
        case 3:
            cin >> u >> v;
            r[v] += w[u], cur += w[u];
            break;
        case 4:
            cin >> v;
            cur += g[v] - r[v], r[v] = g[v];
            break;
        }
        cout << (cur == sum ? "YES\n" : "NO\n");
    }
    return 0;
}