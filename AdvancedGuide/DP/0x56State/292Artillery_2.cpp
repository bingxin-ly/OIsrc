#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, m, p[12], f[N][60000];
char mp[N][12];

void dfs(int row, int col, int pre, int cur, int cnt, int lst) {
    if (col == m) return f[row][cur] = max(f[row][cur], f[row - 1][pre] + cnt), void();
    if (pre / p[col] % 3 == 2)
        dfs(row, col + 1, pre, cur + p[col], cnt, lst);
    else if (pre / p[col] % 3 == 1)
        dfs(row, col + 1, pre, cur, cnt, lst);
    else {
        if (mp[row][col] == 'P' && col - lst > 2)
            dfs(row, col + 1, pre, cur + 2 * p[col], cnt + 1, col);
        dfs(row, col + 1, pre, cur, cnt, lst);
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> mp[i];

    p[0] = 1;
    for (int i = 1; i <= m; i++) p[i] = p[i - 1] * 3;

    memset(f, ~0x3f, sizeof(f)), f[0][0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p[m]; j++)
            if (f[i][j] >= 0) dfs(i + 1, 0, j, 0, 0, -3);
    int ans = 0;
    for (int j = 0; j < p[m]; j++) ans = max(ans, f[n][j]);
    cout << ans;
    return 0;
}