#include <bits/stdc++.h>
using namespace std;

bool s[5][5], m[5][5];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    char c;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++) cin >> c, s[i][j] = c == '+';
    int ans = (1 << 16) - 1;
    for (int i = 1; i < 1 << 16; i++) {
        int row[5]{}, col[5]{};
        memcpy(m, s, sizeof(s));
        for (int x = 1; x <= 4; x++)
            for (int y = 1; y <= 4; y++) {
                int p = (x - 1) * 4 + y - 1;
                if (i >> p & 1) m[x][y] ^= 1, row[x] += 1, col[y] += 1;
            }
        bool clr = 0;
        for (int x = 1; x <= 4; x++)
            for (int y = 1; y <= 4; y++) clr |= m[x][y] ^ ((row[x] + col[y]) & 1);
        if (!clr && __builtin_popcount(i) < __builtin_popcount(ans)) ans = i;
    }
    cout << __builtin_popcount(ans) << '\n';
    for (int x = 1; x <= 4; x++)
        for (int y = 1; y <= 4; y++) {
            int p = (x - 1) * 4 + y - 1;
            if (ans >> p & 1) cout << x << ' ' << y << '\n';
        }
    return 0;
}