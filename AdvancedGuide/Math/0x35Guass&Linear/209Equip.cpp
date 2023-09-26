#include <bits/stdc++.h>
using namespace std;

constexpr int N = 509;
int n, m, c[N];
long double a[N][N], eps = 1e-8;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) cin >> c[i];
    int dim = 0, ans = 0;
    for (int i = 1; i <= m; i++) {
        int cur = 0;
        for (int j = dim + 1; j <= n; j++)
            if (fabs(a[j][i]) > eps && (!cur || c[j] < c[cur])) cur = j;
        if (!cur) continue;
        dim += 1, ans += c[cur];
        swap(a[dim], a[cur]), swap(c[dim], c[cur]);
        for (int j = 1; j <= n; j++) {
            if (dim == j || fabs(a[j][i]) < eps) continue;
            long double r = a[j][i] / a[dim][i];
            for (int k = i; k <= m; k++) a[j][k] -= a[dim][k] * r;
        }
    }
    cout << dim << ' ' << ans;
    return 0;
}