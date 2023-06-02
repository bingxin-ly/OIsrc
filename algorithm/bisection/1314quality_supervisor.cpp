#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10;
int n, m, w[N], v[N];
int nsum[N], vsum[N], l[N], r[N];

int check(int W)
{
    memset(nsum, 0, sizeof(nsum)), memset(vsum, 0, sizeof(vsum));
    for (int i = 1; i <= n; i++)
        nsum[i] = nsum[i - 1] + (w[i] >= W), vsum[i] = vsum[i - 1] + (w[i] >= W) * v[i];

    int cnt = 0;
    for (int i = 1; i <= m; i++)
        cnt += (nsum[r[i]] - nsum[l[i] - 1]) * (vsum[r[i]] - vsum[l[i] - 1]);
    return cnt;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int s;
    cin >> n >> m >> s;

    for (int i = 1; i <= n; i++)
        cin >> w[i] >> v[i];
    for (int i = 1; i <= m; i++)
        cin >> l[i] >> r[i];

    int ll = 1, rr = 1e6 + 1, ans = LLONG_MAX;
    while (ll < rr)
    {
        int mid = (ll + rr) >> 1, res = check(mid);
        if (res > s)
            ll = mid + 1;
        else
            rr = mid;
        ans = min(ans, abs(res - s)); // 保险的记录 mid 值
    }
    cout << ans;
    return 0;
}