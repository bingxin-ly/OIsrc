#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e4 + 9;
int n, cnt[N], v[N], miu[N];
void mobius() {
    fill(miu, miu + N, 1);
    for (int i = 2; i < N; i++) {
        if (v[i]) continue;
        miu[i] = -1;
        for (int j = 2 * i; j < N; j += i)
            v[j] = 1, miu[j] = j / i % i ? -miu[j] : 0;
    }
}
long long C(int n) {  // m = 4
    if (n < 4) return 0;
    return 1ll * n * (n - 1) * (n - 2) * (n - 3) / 24;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    mobius();
    while (cin >> n) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1, x; i <= n; i++) {
            cin >> x;
            for (int j = 1; j <= x / j; j++)
                if (!(x % j)) cnt[j] += 1, cnt[x / j] += j != x / j;
        }
        if (n < 4) {
            cout << "0\n";
            continue;
        }
        long long ans = 0;
        for (int i = 1; i < N; i++) ans += miu[i] * C(cnt[i]);
        cout << ans << '\n';
    }
    return 0;
}