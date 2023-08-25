#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
constexpr double eps = 1e-6, INF = 1e18;
int n, vis[N];
struct
{
    int x, y, z;
} p[N];
double a[N][N], b[N][N], c[N][N], ner[N];
bool check(double k)
{
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            c[i][j] = c[j][i] = a[i][j] - k * b[i][j];
    memset(vis, 0, sizeof(vis));
    fill(ner + 1, ner + n + 1, INF), ner[1] = 0;
    double ret = 0;
    for (int i = 1; i <= n; i++)
    {
        int u = 0;
        for (int i = 1; i <= n; i++)
            if (!vis[i] && (!u || ner[i] < ner[u]))
                u = i;
        vis[u] = 1, ret += ner[u];
        for (int i = 1; i <= n; i++)
            ner[i] = min(ner[i], c[u][i]);
    }
    return ret >= 0;
}
void solve()
{
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y >> p[i].z;
    double sum = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            sum += a[i][j] = a[j][i] = abs(p[i].z - p[j].z);
            b[i][j] = b[j][i] = sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) +
                                     (p[i].y - p[j].y) * (p[i].y - p[j].y));
        }
    double l = 0, r = sum;
    while (l + eps <= r)
    {
        double mid = (l + r) / 2;
        check(mid) ? l = mid : r = mid;
    }
    cout << fixed << setprecision(3) << l << '\n';
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n, n)
        solve();
    return 0;
}