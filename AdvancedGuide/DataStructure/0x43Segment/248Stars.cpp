#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e4 + 9;
int n, w, h, mnv[N << 2], tag[N << 2];
vector<unsigned> ys;
struct S {
    unsigned x, y1, y2;
    int c;
} s[N];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushdown(int p) {
    if (tag[p]) {
        mnv[ls] += tag[p], tag[ls] += tag[p];
        mnv[rs] += tag[p], tag[rs] += tag[p];
        tag[p] = 0;
    }
}
void update(int p, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) return mnv[p] += v, tag[p] += v, void();
    pushdown(p);
    int m = (l + r) >> 1;
    if (ql <= m) update(ls, l, m, ql, qr, v);
    if (qr > m) update(rs, m + 1, r, ql, qr, v);
    mnv[p] = max(mnv[ls], mnv[rs]);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> w >> h) {
        ys.clear(), memset(mnv, 0, sizeof(mnv)), memset(tag, 0, sizeof(tag));
        unsigned x, y;
        for (int i = 1, c; i <= n; i++) {
            cin >> x >> y >> c;
            ys.emplace_back(y), ys.emplace_back(y + h - 1);
            s[i] = {x, y, y + h - 1, c}, s[i + n] = {x + w, y, y + h - 1, -c};
        }
        n <<= 1, sort(s + 1, s + n + 1, [](S a, S b) {
            return a.x < b.x || (a.x == b.x && a.c < b.c);
        });
        sort(ys.begin(), ys.end()), ys.erase(unique(ys.begin(), ys.end()), ys.end());

        int ans = 0;
        for (int i = 1; i < n; i++) {
            s[i].y1 = lower_bound(ys.begin(), ys.end(), s[i].y1) - ys.begin() + 1;
            s[i].y2 = lower_bound(ys.begin(), ys.end(), s[i].y2) - ys.begin() + 1;
            update(1, 1, ys.size(), s[i].y1, s[i].y2, s[i].c);
            ans = max(ans, mnv[1]);
        }
        cout << ans << '\n';
    }
    return 0;
}