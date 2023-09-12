#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
constexpr double eps = 1e-7;
int n, s[N];
double f[N];
struct day {
    int i;
    double a, b, r, k, x, y;
} D[N], T[N];

double slope(int i, int j) {
    if (abs(D[j].x - D[i].x) < eps) return 1e9;
    return (D[j].y - D[i].y) / (D[j].x - D[i].x);
}
void cdq(int l, int r) {
    if (l == r) {
        f[l] = max(f[l], f[l - 1]);
        D[l].y = f[l] / (D[l].a * D[l].r + D[l].b), D[l].x = D[l].r * D[l].y;
        return;
    }
    int m = (l + r) >> 1;
    int t1 = l, t2 = m + 1, t = 0;
    for (int i = l; i <= r; i++)
        if (D[i].i <= m)
            T[t1++] = D[i];
        else
            T[t2++] = D[i];
    memcpy(D + l, T + l, (r - l + 1) * sizeof(day));
    cdq(l, m);

    for (int i = l; i <= m; i++) {
        while (t > 1 && slope(s[t - 1], s[t]) <= slope(s[t - 1], i) + eps) t--;
        s[++t] = i;
    }
    for (int i = m + 1; i <= r; i++) {
        while (t > 1 && slope(s[t - 1], s[t]) <= D[i].k + eps) t--;
        f[D[i].i] = max(f[D[i].i], D[s[t]].x * D[i].a + D[s[t]].y * D[i].b);
    }

    cdq(m + 1, r);
    t1 = l, t2 = m + 1;
    for (int i = l; i <= r; i++)
        if (t1 <= m && (t2 > r || D[t1].x < D[t2].x))
            T[i] = D[t1++];
        else
            T[i] = D[t2++];
    memcpy(D + l, T + l, (r - l + 1) * sizeof(day));
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> f[0];
    for (int i = 1; i <= n; i++) {
        cin >> D[i].a >> D[i].b >> D[i].r;
        D[i].k = -D[i].a / D[i].b, D[i].i = i;
    }
    sort(D + 1, D + n + 1, [](day x, day y) { return x.k < y.k; }), cdq(1, n);
    cout << fixed << setprecision(3) << f[n];
    return 0;
}