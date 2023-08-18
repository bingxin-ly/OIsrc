#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e3 + 5;
int n;
double x[N], y[N], f[N][N][2];
struct
{
    int l, r, p;
} p, fa[N][N][2];
int fix(int $) { return ($ <= 0) && ($ += n), ($ > n) && ($ -= n), $; }
bool ckmin(double &a, double b) { return b < a ? a = b, true : false; }
double squ(double $) { return $ * $; }
double dist(int a, int b) { return sqrt(squ(x[a] - x[b]) + squ(y[a] - y[b])); }
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    int t = 1;
    for (int i = 1; i <= n; i++)
        if (y[i] > y[t])
            t = i;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            f[i][j][0] = f[i][j][1] = 1e18;
    f[0][0][0] = f[0][0][1] = 0;
    for (int k = 2; k <= n; k++)
        for (int l = 0; l < k; l++)
        {
            int r = -l + k - 1;
            if (l && ckmin(f[l][r][0], f[l - 1][r][0] + dist(fix(t + l), fix(t + l - 1))))
                fa[l][r][0] = {l - 1, r, 0};
            if (l && ckmin(f[l][r][0], f[l - 1][r][1] + dist(fix(t + l), fix(t - r))))
                fa[l][r][0] = {l - 1, r, 1};
            if (r && ckmin(f[l][r][1], f[l][r - 1][0] + dist(fix(t - r), fix(t + l))))
                fa[l][r][1] = {l, r - 1, 0};
            if (r && ckmin(f[l][r][1], f[l][r - 1][1] + dist(fix(t - r), fix(t - r + 1))))
                fa[l][r][1] = {l, r - 1, 1};
        }
    double ans = 1e18;
    for (int i = 0; i < n; i++)
    {
        if (f[i][n - i - 1][0] < ans)
            ans = f[i][n - i - 1][0], p = {i, n - i - 1, 0};
        if (f[i][n - i - 1][1] < ans)
            ans = f[i][n - i - 1][1], p = {i, n - i - 1, 1};
    }
    cout << t << ' ';
    stack<int> s;
    while (p.l > 0 || p.r > 0)
        s.emplace(p.p ? fix(t - p.r) : fix(t + p.l)), p = fa[p.l][p.r][p.p];
    while (!s.empty())
        cout << s.top() << ' ', s.pop();
    return 0;
}