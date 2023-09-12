#include <bits/stdc++.h>
#define calc(j, i) (f[j] + power(abs(s[i] - s[j] - L), P))
using namespace std;

constexpr int N = 1e5 + 5;
int n, L, P, s[N], c[N];
char str[N][32];
void print(int i) {
    if (!i) return;
    print(c[i]);
    for (int j = c[i] + 1; j < i; j++) cout << str[j] << ' ';
    cout << str[i] << '\n';
}

struct {
    int p, l, r;
} q[N];
long double f[N];
long double power(long double a, int b) {
    long double res = 1;
    for (; b; b >>= 1, a *= a)
        if (b & 1) res *= a;
    return res;
}
void solve() {
    cin >> n >> L >> P, L += 1;
    for (int i = 1; i <= n; i++)
        cin >> str[i], s[i] = s[i - 1] + strlen(str[i]) + 1;
    int l = 1, r = 1;
    q[1] = {0, 1, n};
    for (int i = 1; i <= n; i++) {
        if (q[l].r == i - 1) l++;
        c[i] = q[l].p, f[i] = calc(q[l].p, q[l].l = i);
        while (l <= r && calc(i, q[r].l) <= calc(q[r].p, q[r].l)) r--;
        int o = q[r].l + 1, p = n + 1;
        while (o < p) {
            int m = (o + p) >> 1;
            (calc(i, m) <= calc(q[r].p, m) ? p = m : o = m + 1);
        }
        if (o > n) continue;
        q[r].r = o - 1, q[++r] = {i, o, n};
    }
    if (f[n] > 1e18)
        cout << "Too hard to arrange\n";
    else
        cout << (long long)f[n] << '\n', print(n);
    cout << "--------------------\n";
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}