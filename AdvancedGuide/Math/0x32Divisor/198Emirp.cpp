#include <bits/stdc++.h>
using namespace std;

long long n, p[]{0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29}, c[11]{INT_MAX};
long long cnt = 1, ans = INT_MAX;
void dfs(long long now, long long num, long long tot) {
    if (now == 11) {
        if (tot > cnt || (tot == cnt && num < ans))
            cnt = tot, ans = num;
        return;
    }
    long long cur = num;
    for (int i = 0; i <= c[now - 1]; i++) {
        if (cur > n) break;
        c[now] = i;
        dfs(now + 1, cur, tot * (i + 1));
        cur *= p[now];
    }
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n, dfs(1, 1, 1), cout << ans;
    return 0;
}