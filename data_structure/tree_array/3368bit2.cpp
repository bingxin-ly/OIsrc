#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 9;
int n, m, a[N], t[N];
void insert(int p, int v) {
    while (p <= n) t[p] += v, p += p & -p;
}
int presum(int p) {
    int r = 0;
    while (p) r += t[p], p -= p & -p;
    return r;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) insert(i, a[i] - a[i - 1]);
    for (int o, x, y, k; m--;) {
        cin >> o;
        if (o == 1)
            cin >> x >> y >> k, insert(x, k), insert(y + 1, -k);
        else
            cin >> x, cout << presum(x) << '\n';
    }
    return 0;
}