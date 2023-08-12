#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
constexpr double eps = 1e-6;
int n, s, t;
int o[N], a[N], b[N], k[N];
int c[N], x[N];

int len[N];
double dis[N];
vector<pair<int, double>> g[N];
bool dijk(double T)
{
    queue<int> q;
    for (int i = 0; i <= n; i++)
        len[i] = dis[i] = 0, g[i].clear(), q.emplace(i);
    for (int i = 1; i <= s; i++)
        if (o[i] == 1)
        {
            if (k[i] - T < eps)
                continue;
            g[a[i]].emplace_back(b[i], -log(k[i] - T));
        }
        else
            g[a[i]].emplace_back(b[i], log(k[i] + T));
    for (int i = 1; i <= t; i++)
        g[0].emplace_back(c[i], log(x[i])),
            g[c[i]].emplace_back(0, -log(x[i]));
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (const auto &[v, w] : g[u])
            if (dis[v] > dis[u] + w + eps)
            {
                dis[v] = dis[u] + w, len[v] = len[u] + 1, q.emplace(v);
                if (len[v] >= n)
                    return true;
            }
    }
    return false;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> s >> t;
    for (int i = 1; i <= s; i++)
        cin >> o[i] >> a[i] >> b[i] >> k[i];
    for (int i = 1; i <= t; i++)
        cin >> c[i] >> x[i];
    if (!dijk(0))
        return cout << -1, 0;
    double l = 0, r = 1e9;
    while (r - l > eps)
    {
        double m = (l + r) / 2;
        dijk(m) ? l = m : r = m;
    }
    cout << fixed << setprecision(6) << l;
    return 0;
}