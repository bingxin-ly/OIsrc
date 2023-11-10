#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, a[N], t[N];
void add(int p, int v) {
    for (; p <= n; p += p & -p) t[p] += v;
}
int sum(int p) {
    int v = 0;
    for (; p; p -= p & -p) v += t[p];
    return v;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    char c;
    for (int l, r, d; m--;) {
        cin >> c;
        if (c == 'C')
            cin >> l >> r >> d, add(l, d), add(r + 1, -d);
        else
            cin >> d, cout << a[d] + sum(d) << '\n';
    }
    return 0;
}