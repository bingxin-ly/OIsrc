#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, K = 320;
int pos[N], st[K], ed[K];
int arr[N], cnt[N], sum[K][N], ans[K][K];

int query(int l, int r)
{
    int sid = pos[l], eid = pos[r], res = 0;
    if (sid == eid)
    {
        for (int i = l; i <= r; i++)
        {
            cnt[arr[i]] += 1;
            if (!(cnt[arr[i]] & 1))
                res += 1;
            else if (cnt[arr[i]] > 2)
                res -= 1;
        }
        for (int i = l; i <= r; i++)
            cnt[arr[i]] -= 1;
        return res;
    }

    res = ans[sid + 1][eid - 1];
    for (int i = l; i <= ed[sid]; i++)
    {
        cnt[arr[i]] += 1;
        int tmp = sum[eid - 1][arr[i]] - sum[sid][arr[i]];
        if (!(cnt[arr[i]] + tmp & 1))
            res += 1;
        else if (cnt[arr[i]] + tmp > 2)
            res -= 1;
    }
    for (int i = st[eid]; i <= r; i++)
    {
        cnt[arr[i]] += 1;
        int tmp = sum[eid - 1][arr[i]] - sum[sid][arr[i]];
        if (!(cnt[arr[i]] + tmp & 1))
            res += 1;
        else if (cnt[arr[i]] + tmp > 2)
            res -= 1;
    }
    for (int i = l; i <= ed[sid]; i++)
        cnt[arr[i]] -= 1;
    for (int i = st[eid]; i <= r; i++)
        cnt[arr[i]] -= 1;
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, c, m;
    cin >> n >> c >> m;
    int len = sqrt(n), num = (n - 1) / len + 1;
    for (int i = 1; i <= n; i++)
    {
        pos[i] = (i - 1) / len + 1;
        cin >> arr[i], sum[pos[i]][arr[i]] += 1;
    }

    for (int i = 1; i <= num; i++)
    {
        st[i] = (i - 1) * len + 1, ed[i] = i * len;
        for (int j = 0; j <= c; j++)
            sum[i][j] += sum[i - 1][j];
    }
    ed[num] = n;

    for (int i = 1; i <= num; i++)
    {
        for (int j = i; j <= num; j++)
        {
            ans[i][j] = ans[i][j - 1];
            for (int k = st[j]; k <= ed[j]; k++)
            {
                cnt[arr[k]] += 1;
                if (!(cnt[arr[k]] & 1))
                    ans[i][j] += 1;
                else if (cnt[arr[k]] > 2)
                    ans[i][j] -= 1;
            }
        }
        memset(cnt, 0, sizeof cnt);
    }

    for (int l, r, lst = 0; m--;)
    {
        cin >> l >> r;
        l = (l + lst) % n + 1, r = (r + lst) % n + 1;
        if (l > r)
            l ^= r ^= l ^= r;
        cout << (lst = query(l, r)) << '\n';
    }
    return 0;
}