#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e3 + 9;
long long t, k, c[N][N], s[N][N];
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> t >> k;
    c[0][0] = 1;
    for (int i = 1; i <= 2000; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % k;
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + !c[i][j];
        }
        s[i][i + 1] = s[i][i];
    }
    for (int n, m; t--;)
        cin >> n >> m, cout << s[n][min(n, m)] << '\n';
    return 0;
}