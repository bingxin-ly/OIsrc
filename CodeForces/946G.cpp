#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 9;
int n, m, a[N], b[N], c[N], f[N][2];
struct {
    int t[N << 1];
    void update(int p, int v) {
        for (; p <= m; p += p & -p) t[p] = max(t[p], v);
    }
    int premax(int p) {
        int v = 0;
        for (; p; p -= p & -p) v = max(v, t[p]);
        return v;
    }
} bit[3];

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    vector<int> num;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        num.emplace_back(a[i] - i), num.emplace_back(a[i] - i + 1);
    }
    sort(num.begin(), num.end());
    num.resize(m = unique(num.begin(), num.end()) - num.begin());
    for (int i = 1; i <= n; i++)
        b[i] = lower_bound(num.begin(), num.end(), a[i] - i) - num.begin() + 1,
        c[i] = lower_bound(num.begin(), num.end(), a[i] - i + 1) - num.begin() + 1;
    for (int i = 1; i <= n; i++) {
        if (i > 1) bit[0].update(b[i - 1], f[i - 1][0]);
        if (i > 1) bit[1].update(b[i - 1], f[i - 1][1]);
        if (i > 2) bit[2].update(b[i - 2], f[i - 2][0]);
        f[i][0] = bit[0].premax(b[i]) + 1;
        if (i > 1) f[i][1] = max(bit[1].premax(b[i]), bit[2].premax(c[i])) + 1;
    }
    int ans = 0;
    for (int i = 1; i < n; i++) ans = max(ans, f[i][0]);
    for (int i = 2; i <= n; i++) ans = max(ans, f[i][1]);
    cout << n - 1 - ans;
    return 0;
}