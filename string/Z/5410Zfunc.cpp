#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e7 + 5;
char a[N], b[N];
int n, m, z[N], p[N];

signed main() {
    cin >> (a + 1) >> (b + 1), n = strlen(a + 1), m = strlen(b + 1);
    z[1] = m;
    int l = 0, r = 0;
    for (int i = 2; i <= m; i++) {
        z[i] = i <= r ? min(z[i - l + 1], r - i + 1) : 0;
        while (b[1 + z[i]] == b[i + z[i]])
            z[i] += 1;
        if (r < i + z[i] - 1)
            r = i + z[i] - 1, l = i;
    }
    l = r = 0;
    for (int i = 1; i <= n; i++) {
        p[i] = i <= r ? min(z[i - l + 1], r - i + 1) : 0;
        while (1 + p[i] <= m && b[1 + p[i]] == a[i + p[i]])
            p[i] += 1;
        if (r < i + p[i] - 1)
            r = i + p[i] - 1, l = i;
    }
    long long ans = 0;
    for (int i = 1; i <= m; i++)
        ans ^= i * (z[i] + 1ll);
    cout << ans << '\n';
    ans = 0;
    for (int i = 1; i <= n; i++)
        ans ^= i * (p[i] + 1ll);
    cout << ans << '\n';
    return 0;
}