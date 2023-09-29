#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1009;
int n, m, dif[N][N];

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int x1, y1, x2, y2; m--;) {
        cin >> x1 >> y1 >> x2 >> y2;
        dif[x1][y1] += 1;
        dif[x1][y2 + 1] -= 1, dif[x2 + 1][y1] -= 1;
        dif[x2 + 1][y2 + 1] += 1;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dif[i][j] += dif[i - 1][j] + dif[i][j - 1] - dif[i - 1][j - 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << dif[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}