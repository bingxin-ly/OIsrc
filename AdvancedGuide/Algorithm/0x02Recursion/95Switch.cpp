// 注意 OJ 题意与书上的有出入
#include <bits/stdc++.h>
using namespace std;

bool sav[6][6], lit[6][6];
int ans, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
void click(int x, int y) {
    ans += 1, lit[x][y] ^= 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || nx > 5 || ny < 1 || ny > 5) continue;
        lit[nx][ny] ^= 1;
    }
}
int calc() {
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 5; j++)
            if (!lit[i][j]) {
                click(i + 1, j);
                if (ans > 6) return 0x3f3f3f3f;
            }
    for (int j = 1; j <= 5; j++)
        if (!lit[5][j]) return 0x3f3f3f3f;
    return ans;
}
int solve() {
    char s[7];
    for (int i = 1; i <= 5; i++) {
        cin >> (s + 1);
        for (int j = 1; j <= 5; j++)
            sav[i][j] = s[j] - '0';
    }

    int ret = 0x3f3f3f3f;
    for (int i = 0; i < 1 << 5; i++) {
        memcpy(lit, sav, sizeof(sav)), ans = 0;
        for (int j = 0; j < 5; j++)
            if (i >> j & 1) click(1, j + 1);
        ret = min(ret, calc());
    }
    cout << (ret != 0x3f3f3f3f ? ret : -1) << '\n';
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    while (n--) solve();
    return 0;
}