#include <bits/stdc++.h>
#define Y(j) (f[j] + squ(p[j + 1].l) - 2 * p[j + 1].l - s[j])
#define X(i) (p[i + 1].l)
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, k, q[N];
struct seg {
    int l, r;
} p[N];
long long s[N], f[N], g[N], ans;

long long squ(int $) { return 1ll * $ * $; }
double slope(int i, int j) { return 1.0 * (Y(j) - Y(i)) / (X(j) - X(i)); }
bool ok(long long C) {
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        while (l < r && slope(q[l], q[l + 1]) < 2 * p[i].r) l++;
        f[i] = f[q[l]] + squ(p[i].r - p[q[l] + 1].l + 1) - s[q[l]] + C;
        g[i] = g[q[l]] + 1;
        while (l < r && slope(q[r - 1], q[r]) >= slope(q[r - 1], i)) r--;
        q[++r] = i;
    }
    if (g[n] <= k) ans = f[n] - C * k;
    return g[n] <= k;
}
signed main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].l >> p[i].r;
        if (p[i].l > p[i].r) swap(p[i].l, p[i].r);
    }

    sort(p + 1, p + n + 1, [](seg x, seg y) { return x.l != y.l ? x.l < y.l : x.r > y.r; });
    int c = 0;
    for (int i = 1, r = -1; i <= n; i++)
        if (p[i].r > r) r = p[i].r, p[++c] = p[i];
    n = c;

    for (int i = 1; i < n; i++)
        if (p[i].r >= p[i + 1].l) s[i] = squ(p[i].r - p[i + 1].l + 1);
    long long l = 0, r = 1ll * m * m;
    while (l <= r) {
        long long s = (l + r) >> 1;
        ok(s) ? r = s - 1 : l = s + 1;
    }
    cout << ans;
    return 0;
}