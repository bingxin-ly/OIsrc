#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, m, vad[N][N], f[N][N][N];
char mp[N][12];
vector<int> s;
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> mp[i];
    for (int i = 0; i < 1 << m; i++) {
        if (i & i >> 1 || i & i >> 2) continue;
        s.emplace_back(i);
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < (int)s.size(); j++)
            vad[i][j] = [&]() {
                for (int k = 0; k < m; k++)
                    if ((s[j] >> k & 1) && mp[i][k] == 'H') return false;
                return true;
            }();
    memset(f, ~0x3f, sizeof(f)), f[0][0][0] = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < (int)s.size(); j++) {
            if (!vad[i][j]) continue;
            for (int k = 0; k < (int)s.size(); k++) {
                if (s[j] & s[k] || (i > 1 && !vad[i - 1][k])) continue;
                for (int l = 0; l < (int)s.size(); l++) {
                    if (s[j] & s[l]) continue;
                    f[i][j][k] = max(f[i][j][k], f[i - 1][k][l] + __builtin_popcount(s[j]));
                }
                if (i == n) ans = max(ans, f[i][j][k]);
            }
        }
    cout << ans;
    return 0;
}