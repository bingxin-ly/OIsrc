#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, K = 320;
int len, num, pos[N], st[K], ed[K];
int arr[N], cov[K];

int force(int l, int r, int v)
{
    int id = pos[l], res = 0;
    if (cov[id])
        res += (cov[id] == v) * (r - l + 1);
    else
        for (int i = l; i <= r; i++)
            res += arr[i] == v;
    if (cov[id])
        for (int i = st[id]; i <= ed[id]; i++)
            if (i < l || i > r)
                arr[i] = cov[id];
    for (int i = l; i <= r; i++)
        arr[i] = v;
    cov[id] = 0;
    return res;
}
int solve(int l, int r, int v)
{
    // 左端块是肯定的要暴力的，右端块 if 判一下
    // 整块 for 可以直接写，因为不满足就直接跳出来了
    int sid = pos[l], eid = pos[r], ans = 0;
    ans += force(l, min(r, ed[sid]), v);

    if (sid != eid)
        ans += force(st[eid], r, v);

    for (int i = sid + 1; i <= eid - 1; i++)
    {
        if (cov[i])
            ans += (cov[i] == v) * len;
        else
            for (int j = st[i]; j <= ed[i]; j++)
                ans += arr[j] == v;
        cov[i] = v;
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    len = sqrt(n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1,
        ed[i] = i * len;
    for (int i = 1; i <= n; i++)
        pos[i] = (i - 1) / len + 1, cin >> arr[i];
    for (int l, r, c; n--;)
    {
        cin >> l >> r >> c;
        cout << solve(l, r, c) << '\n';
    }
    return 0;
}