#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 10000;
void mul(int F[], int I[][2]) {
    int G[] = {0, 0};
    for (int j = 0; j < 2; j++)
        for (int k = 0; k < 2; k++)
            (G[j] += F[k] * I[k][j] % MOD) %= MOD;
    memcpy(F, G, sizeof(G));
}
void mull(int I[][2]) {
    int G[][2] = {0, 0, 0, 0};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                G[i][k] += 1ll * I[i][j] * I[j][k] % MOD;
    memcpy(I, G, sizeof(G));
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    while (cin >> n, ~n) {
        int F[] = {0, 1}, I[][2] = {0, 1, 1, 1};
        for (; n; n >>= 1) {
            if (n & 1) mul(F, I);
            mull(I);
        }
        cout << F[0] << '\n';
    }
    return 0;
}