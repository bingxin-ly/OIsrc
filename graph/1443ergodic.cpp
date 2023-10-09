#include <bits/stdc++.h>
using namespace std;

constexpr int N = 409;
int n, m, x, y, s[N][N],
    dx[]{2, 2, 1, 1, -1, -1, -2, -2}, dy[]{1, -1, 2, -2, 2, -2, 1, -1};
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> x >> y;
    queue<pair<int, int> > q;
    q.emplace(x, y), memset(s, -1, sizeof(s)), s[x][y] = 0;
    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();
        for (int i = 0; i < 8; i++) {
            int nx = cx + dx[i], ny = cy + dy[i];
            if (nx < 1 || ny < 1 || nx > n || ny > m || s[nx][ny] != -1) continue;
            s[nx][ny] = s[cx][cy] + 1, q.emplace(nx, ny);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cout << s[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}