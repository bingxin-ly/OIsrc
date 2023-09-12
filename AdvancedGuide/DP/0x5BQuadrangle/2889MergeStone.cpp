#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5005;
int n, s[N], f[N][N], p[N][N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1];
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++) f[i][i] = 0, p[i][i] = i;
    for (int i = 2; i <= n; i++)
        for (int l = 1; l <= n - i + 1; l++) {
            int r = l + i - 1;
            for (int k = p[l][r - 1]; k <= p[l + 1][r]; k++)
                if (f[l][r] > f[l][k] + f[k + 1][r] + s[r] - s[l - 1])
                    f[l][r] = f[l][k] + f[k + 1][r] + s[r] - s[l - 1],
                    p[l][r] = k;
        }
    cout << f[1][n];
    return 0;
}