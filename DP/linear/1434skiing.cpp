#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int r, c, a[N][N], f[N][N];
struct poi
{
    int x, y;
    poi(int x_, int y_) : x(x_), y(y_) {}
    bool operator<(const poi &p) const { return a[x][y] < a[p.x][p.y]; }
};
vector<poi> ps;
inline void ckmax(int &x, int y) { (y > x) && (x = y); }
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> r >> c;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            cin >> a[i][j], ps.emplace_back(i, j);
    sort(ps.begin(), ps.end());
    int ans = 0;
    for (const poi &i : ps)
    {
        const int &x = i.x, &y = i.y;
        if (y + 1 <= c && a[x][y + 1] < a[x][y])
            ckmax(f[x][y], f[x][y + 1]);
        if (y - 1 >= 1 && a[x][y - 1] < a[x][y])
            ckmax(f[x][y], f[x][y - 1]);
        if (x + 1 <= r && a[x + 1][y] < a[x][y])
            ckmax(f[x][y], f[x + 1][y]);
        if (x - 1 >= 1 && a[x - 1][y] < a[x][y])
            ckmax(f[x][y], f[x - 1][y]);
        ans = max(ans, ++f[x][y]);
    }
    cout << ans;
    return 0;
}