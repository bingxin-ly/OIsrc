#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 9;
int n, m, ST[N][18];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> ST[i][0];
    for (int l = 1; (1 << l) <= n; l++)
        for (int i = 1; i + (1 << l) - 1 <= n; i++)
            ST[i][l] = max(ST[i][l - 1], ST[i + (1 << (l - 1))][l - 1]);
    for (int l, r; m--;) {
        cin >> l >> r;
        int k = __lg(r - l + 1);
        cout << max(ST[l][k], ST[r - (1 << k) + 1][k]) << '\n';
    }
    return 0;
}