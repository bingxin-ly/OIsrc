// 一个优化思路：尝试上一次的回文半径，不相等则可以直接跳过
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6 + 9, P = 131;
int n, c;
char s[N];
unsigned long long p[N], ph[N], rh[N];

bool check(int l, int l1, int l2) {
    int r1 = l1 + l - 1, r2 = l2 + l - 1;
    return ph[r1] - ph[l1 - 1] * p[l] == rh[l2] - rh[r2 + 1] * p[l];
}
void solve() {
    n = strlen(s + 1), rh[n + 1] = 0, p[0] = 1;
    for (int i = 1, j = n; i <= n; i++, j--)
        ph[i] = ph[i - 1] * P + (s[i] - 'a' + 1),
        rh[j] = rh[j + 1] * P + (s[j] - 'a' + 1),
        p[i] = p[i - 1] * P;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = 0, p = 1;
        while (p)
            if (i - l - p >= 1 && i + l + p <= n &&
                check(l + p, i - l - p, i + 1))
                l += p, p <<= 1;
            else
                p >>= 1;
        ans = max(ans, 2 * l + 1);
    }
    for (int i = 1; i < n; i++) {
        int l = 0, p = 1;
        while (p) {
            if (i - l - p >= 0 && i + l + p <= n &&
                check(l + p, i - l - p + 1, i + 1))
                l += p, p <<= 1;
            else
                p >>= 1;
        }
        ans = max(ans, 2 * l);
    }
    cout << "Case " << ++c << ": " << ans << "\n";
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> (s + 1), s[1] != 'E') solve();
    return 0;
}