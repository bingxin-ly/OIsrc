#include <bits/stdc++.h>
using namespace std;

int n, k, m, a[62][62], b[62][62];
void mul(int a[][62], int b[][62]) {
    int c[62][62]{};
    for (int i = 1; i <= n << 1; i++)
        for (int j = 1; j <= n << 1; j++)
            for (int k = 1; k <= n << 1; k++)
                (c[i][k] += a[i][j] * b[j][k] % m) %= m;
    memcpy(a, c, sizeof(c));
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k >> m, k += 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> a[i][j];
        a[i][i + n] = a[i + n][i + n] = 1;
        b[i][i] = b[i + n][i + n] = 1;
    }
    for (; k; k >>= 1) {
        if (k & 1) mul(b, a);
        mul(a, a);
    }
    for (int i = 1; i <= n; i++) {
        (b[i][i + n] += m - 1) %= m;
        for (int j = 1; j <= n; j++) cout << b[i][j + n] << ' ';
        cout << '\n';
    }
    return 0;
}