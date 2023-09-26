#include <bits/stdc++.h>
using namespace std;

int n, m;
unsigned long long a[10009];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    for (int C = 1; C <= T; C++) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        int zro = 0, lin = n;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++)
                if (a[j] > a[i]) swap(a[i], a[j]);
            if (!a[i]) {
                zro = 1, lin = i - 1;
                break;
            }
            for (int k = 63; k >= 0; k--)
                if (a[i] >> k & 1) {
                    for (int j = 1; j <= n; j++)
                        if (i != j && a[j] >> k & 1) a[j] ^= a[i];
                    break;
                }
        }
        cin >> m;
        cout << "Case #" << C << ":\n";
        while (m--) {
            unsigned long long k, ans = 0;
            cin >> k, k -= zro;
            if (k >= 1ull << lin)
                cout << -1 << '\n';
            else {
                for (int i = lin - 1; i >= 0; i--)
                    if (k >> i & 1) ans ^= a[lin - i];
                cout << ans << '\n';
            }
        }
    }
    return 0;
}