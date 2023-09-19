#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, h[N], w[N], p, s[N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) cin >> h[i];
        p = h[++n] = 0;
        long long ans = 0;
        for (int i = 1; i <= n; i++)
            if (h[i] > s[p])
                s[++p] = h[i], w[p] = 1;
            else {
                int width = 0;
                while (s[p] > h[i]) {
                    width += w[p], ans = max(ans, 1ll * width * s[p]);
                    p--;
                }
                s[++p] = h[i], w[p] = width + 1;
            }
        cout << ans << '\n';
    }
    return 0;
}