#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e4 + 9;
int c, n, cnt[N << 2];
double len[N << 2];
vector<double> ys;
struct S {
    double x, y1, y2, v;
} s[N];

#define ls (p << 1)
#define rs (p << 1 | 1)
void update(int p, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        cnt[p] += v;
        if (cnt[p])
            len[p] = ys[r] - ys[l - 1];
        else
            len[p] = l == r ? 0 : len[ls] + len[rs];
        return;
    }
    int m = (l + r) >> 1;
    if (ql <= m) update(ls, l, m, ql, qr, v);
    if (qr > m) update(rs, m + 1, r, ql, qr, v);
    len[p] = cnt[p] ? ys[r] - ys[l - 1] : len[ls] + len[rs];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n, n) {
        ys.clear(), memset(cnt, 0, sizeof(cnt)), memset(len, 0, sizeof(len));
        double x1, y1, x2, y2;
        for (int i = 1; i <= n; i++) {
            cin >> x1 >> y1 >> x2 >> y2;
            ys.emplace_back(y1), ys.emplace_back(y2);
            s[i] = {x1, y1, y2, 1}, s[i + n] = {x2, y1, y2, -1};
        }
        n <<= 1, sort(s + 1, s + n + 1, [](S a, S b) { return a.x < b.x; });
        sort(ys.begin(), ys.end()), ys.erase(unique(ys.begin(), ys.end()), ys.end());

        double ans = 0;
        for (int i = 1; i < n; i++) {
            s[i].y1 = lower_bound(ys.begin(), ys.end(), s[i].y1) - ys.begin() + 1;
            s[i].y2 = lower_bound(ys.begin(), ys.end(), s[i].y2) - ys.begin();
            update(1, 1, ys.size() - 1, s[i].y1, s[i].y2, s[i].v);
            ans += len[1] * (s[i + 1].x - s[i].x);
        }
        cout << "Test case #" << ++c << "\n"
             << "Total explored area: " << fixed << setprecision(2) << ans << "\n\n";
    }
    return 0;
}