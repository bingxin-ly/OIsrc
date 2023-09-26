#include <bits/stdc++.h>
using namespace std;

int n, a[100];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        int x, y;
        for (int i = 1; i <= n; i++)
            cin >> x, a[i] ^= x, a[i] |= 1 << i;
        while (cin >> x >> y, x && y) a[y] |= 1 << x;
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++)
                if (a[j] > a[i]) swap(a[i], a[j]);
            if (a[i] == 0) {
                ans = 1 << (n - i + 1);
                break;
            }
            if (a[i] == 1) {
                ans = 0;
                break;
            }
            for (int k = n; k; k--)
                if (a[i] >> k & 1) {
                    for (int j = 1; j <= n; j++)
                        if (i != j && a[j] >> k & 1) a[j] ^= a[i];
                    break;
                }
        }
        if (ans == 0)
            cout << "Oh,it's impossible~!!\n";
        else
            cout << ans << '\n';
    }
    return 0;
}