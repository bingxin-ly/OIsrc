#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
char s[N];
bool equals(int r, int j, int i) {
    for (int k = 0; k < i; k++)
        if (s[r - k] != s[j - k]) return false;
    return true;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static int n, f[N][N], p[N][N];
    while (cin >> (s + 1)) {
        n = strlen(s + 1);
        memset(f, 0x3f, sizeof(f)), memset(p, 0, sizeof(p));
        for (int i = 1; i <= n; i++)
            for (int l = 1; l <= n - i + 1; l++) {
                int r = l + i - 1;
                if (i == 1)
                    f[l][r] = 1;
                else
                    for (int k = l; k < r; k++) {
                        int &cur = f[l][r], upd = f[l][k] + f[k + 1][r];
                        if (cur > upd || ((cur == upd) && p[l][r] < 0)) cur = upd, p[l][r] = k;
                    }
                for (int j = r + i, c = 2; j <= n && equals(r, j, i); j += i, c++) {
                    int &cur = f[l][j], upd = f[l][r] + to_string(c).size() + 2;
                    if (cur > upd) cur = upd, p[l][j] = -i;
                }
            }
        function<void(int, int)> print = [&](int l, int r) {
            if (!p[l][r])
                for (int i = l; i <= r; i++) cout << s[i];
            else if (p[l][r] > 0)
                print(l, p[l][r]), print(p[l][r] + 1, r);
            else {
                int i = -p[l][r];
                cout << (r - l + 1) / i << '(', print(l, l + i - 1), cout << ')';
            }
        };
        print(1, n), cout << '\n';
    }
    return 0;
}