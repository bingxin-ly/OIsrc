#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e4 + 9;
int v[N], miu[N];
void mobius() {
    fill(miu, miu + N, 1);
    for (int i = 2; i < N; i++) {
        if (v[i]) continue;
        miu[i] = -1;
        for (int j = 2 * i; j < N; j += i) {
            v[j] = 1;
            miu[j] = j / i % i ? -miu[j] : 0;
        }
    }
    for (int i = 1; i < N; i++) miu[i] += miu[i - 1];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    mobius();
    int n, a, b, k;
    for (cin >> n; n; n--) {
        cin >> a >> b >> k, a /= k, b /= k;
        if (a > b) swap(a, b);
        int ans = 0;
        for (int x = 1, y; x <= a; x = y + 1) {
            y = min(a / (a / x), b / (b / x));
            ans += (miu[y] - miu[x - 1]) * (a / x) * (b / x);
        }
        cout << ans << '\n';
    }
    return 0;
}