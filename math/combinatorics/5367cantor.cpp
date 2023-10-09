#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 3, M = 998244353;
int n, ans = 1, fac[N], a[N], f[N];
void add(int x, int v) {
    while (x <= n) f[x] += v, x += x & -x;
}
int ask(int x) {
    int s = 0;
    while (x) s += f[x], x -= x & -x;
    return s;
}
int main() {
    cin >> n, fac[0] = 1;
    for (int i = 1; i <= n; i++)
        cin >> a[i], fac[i] = 1ll * fac[i - 1] * i % M, add(i, 1);
    for (int i = 1; i <= n; i++)
        add(a[i], -1), (ans += 1ll * ask(a[i]) * fac[n - i] % M) %= M;
    cout << ans;
    return 0;
}
