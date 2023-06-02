// 这篇有妥协地写了 <= 的形式，在缩小区间时更新答案
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int l, k, ope[N];

int check(int n)
{
    int cnt = 0, tot = 0;
    for (int i = 1; i <= l; i++)
    {
        cnt = max(cnt + ope[i], 0ll);
        if (cnt >= n)
            tot++, cnt = 0;
    }
    return tot;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> l >> k;
    for (int i = 1; i <= l; i++)
        cin >> ope[i];

    int ans1 = -1, ans2 = -1;
    int l = 1, r = LLONG_MAX; // 开小就 WA 了 /cs
    while (l <= r)
    {
        int mid = (l + r) >> 1, res = check(mid);
        if (res > k)
            l = mid + 1;
        else
            r = mid - 1,
            ans1 = res == k ? mid : ans1;
    }

    l = 1, r = 1e18;
    while (l <= r)
    {
        int mid = (l + r) >> 1, res = check(mid);
        if (res >= k)
            l = mid + 1,
            ans2 = res == k ? mid : ans2;
        else
            r = mid - 1;
    }
    if (ans1 == -1)
        cout << -1;
    else
        cout << ans1 << ' ' << ans2;
    return 0;
}