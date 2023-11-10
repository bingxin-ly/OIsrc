#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 9;
int n, p[N], a[N], b[N], t[N];
long long ans;
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
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i];

    memset(t, 0, sizeof(t));
    for (int i = 1; i <= n; i++) a[i] = i - 1 - sum(p[i]), add(p[i], 1);
    memset(t, 0, sizeof(t));
    for (int i = n; i >= 1; i--) b[i] = n - i - sum(p[i]), add(p[i], 1);
    ans = 0;
    for (int i = 1; i <= n; i++) ans += 1ll * a[i] * b[i];
    cout << ans << ' ';

    memset(t, 0, sizeof(t));
    for (int i = 1; i <= n; i++) a[i] = sum(p[i]), add(p[i], 1);
    memset(t, 0, sizeof(t));
    for (int i = n; i >= 1; i--) b[i] = sum(p[i]), add(p[i], 1);
    ans = 0;
    for (int i = 1; i <= n; i++) ans += 1ll * a[i] * b[i];
    cout << ans << ' ';
    return 0;
}