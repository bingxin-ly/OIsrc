#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1e9 + 7;
void mul(int F[], int I[][3]) {
    int G[3]{};
    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++)
            (G[j] += 1ll * F[k] * I[k][j] % M) %= M;
    memcpy(F, G, sizeof(G));
}
void mull(int I[][3]) {
    int G[3][3]{};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                (G[i][k] += 1ll * I[i][j] * I[j][k] % M) %= M;
    memcpy(I, G, sizeof(G));
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T, n;
    for (cin >> T; T; T--) {
        cin >> n;
        int F[] = {0, 1, 1}, I[][3] = {{0, 0, 1}, {1, 0, 0}, {0, 1, 1}};
        for (; n; n >>= 1) {
            if (n & 1) mul(F, I);
            mull(I);
        }
        cout << F[0] << '\n';
    }
    return 0;
}