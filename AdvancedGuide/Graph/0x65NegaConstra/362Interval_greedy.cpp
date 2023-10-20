#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 9;
int n, v[N], t[N], p[N];
struct {
    int l, r, c;
} s[N];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
void add(int p) {
    for (; p < N; p += p & -p) t[p] += 1;
}
int ask(int p) {
    int r = 0;
    for (; p > 0; p -= p & -p) r += t[p];
    return r;
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i].l >> s[i].r >> s[i].c;
    iota(p + 1, p + n + 1, 1);
    sort(s + 1, s + n + 1, [](auto x, auto y) { return x.r < y.r; });
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = s[i].l, r = s[i].r,
            cnt = s[i].c - (ask(r) - ask(l - 1));
        for (int j = r; j >= l && cnt > 0; j = p[j])
            if (!v[j]) {
                cnt--, ans++, v[j] = 1;
                add(j), p[j] = j - 1;
            }
    }
    cout << ans;
    return 0;
}