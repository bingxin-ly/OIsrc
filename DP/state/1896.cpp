#include <bits/stdc++.h>
using namespace std;

constexpr int N = 10;
int n, K, vad[1 << N];
long long f[N][N * N][1 << N];

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> K;
    for (int i = 0; i < 1 << n; i++) vad[i] = !(i >> 1 & i) && !(i << 1 & i);
    for (int i = 0; i < 1 << n; i++) cerr << vad[i] << ' ';
    cerr << endl;

    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 1 << n; j++) {
            if (!vad[j]) continue;
            for (int k = 0; k < 1 << n; k++) {
                if (!vad[k] || j & k || j << 1 & k || j >> 1 & k) continue;
                for (int s = __builtin_popcount(j); s <= K; s++)
                    f[i][s][j] += f[i - 1][s - __builtin_popcount(j)][k];
            }
        }
    long long ans = 0;
    for (int j = 0; j < 1 << n; j++)
        ans += f[n][K][j];
    cout << ans;
    return 0;
}