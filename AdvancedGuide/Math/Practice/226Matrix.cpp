#include <bits/stdc++.h>
using namespace std;

constexpr int N = 14, M = 10000007;
int n, m, a[N], b[N][N];
void mul(int a[], int b[][N]) {
    int c[N]{};
    for (int j = 0; j <= n + 1; j++)
        for (int k = 0; k <= n + 1; k++)
            (c[k] += 1ll * a[j] * b[j][k] % M) %= M;
    memcpy(a, c, sizeof(c));
}
void mull(int b[][N]) {
    int c[N][N]{};
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= n + 1; j++)
            for (int k = 0; k <= n + 1; k++)
                (c[i][k] += 1ll * b[i][j] * b[j][k] % M) %= M;
    memcpy(b, c, sizeof(c));
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m) {
        a[0] = 23, a[n + 1] = 3;
        for (int i = 1; i <= n; i++) cin >> a[i];
        memset(b, 0, sizeof(b));
        b[0][0] = 10, b[n + 1][0] = b[n + 1][n + 1] = 1;
        for (int j = 1; j <= n; j++) {
            b[0][j] = 10, b[n + 1][j] = 1;
            for (int i = 1; i <= j; i++) b[i][j] = 1;
        }
        for (; m; m >>= 1) {
            if (m & 1) mul(a, b);
            mull(b);
        }
        cout << a[n] << '\n';
    }
    return 0;
}