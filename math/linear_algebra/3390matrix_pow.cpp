#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 109, M = 1e9 + 7;
int n, k, a[N][N], b[N][N];
void mul(int a[][N], int b[][N]) {
    int c[N][N]{};
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                (c[i][k] += a[i][j] * b[j][k] % M) %= M;
    memcpy(a, c, sizeof(c));
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> a[i][j];
        b[i][i] = 1;
    }
    for (; k; k >>= 1) {
        if (k & 1) mul(b, a);
        mul(a, a);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << b[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}