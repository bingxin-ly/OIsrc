#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10, K = 710;
int blo[N], st[K], ed[K];
int arr[N], cnt[N], loc[N], f[K][K];
vector<int> pos[N];

int query(int l, int r)
{
    int sid = blo[l], eid = blo[r], ans = 0;
    if (sid == eid)
    {
        for (int i = l; i <= r; i++)
            ans = max(ans, ++cnt[arr[i]]);
        for (int i = l; i <= r; i++)
            cnt[arr[i]] = 0;
        return ans;
    }

    ans = f[sid + 1][eid - 1];
    for (int i = l; i <= ed[sid]; i++)
    {
        int it = loc[i];
        while (it + ans < pos[arr[i]].size() && pos[arr[i]][it + ans] <= r)
            ans += 1;
    }
    for (int i = st[eid]; i <= r; i++)
    {
        int it = loc[i];
        while (it - ans >= 0 && pos[arr[i]][it - ans] >= l)
            ans += 1;
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int len = sqrt(n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1, ed[i] = i * len;
    ed[num] = n;

    for (int i = 1; i <= n; i++)
        blo[i] = (i - 1) / len + 1, cin >> arr[i];
    vector<int> val(arr + 1, arr + n + 1);
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 1; i <= n; i++)
        arr[i] = lower_bound(val.begin(), val.end(), arr[i]) - val.begin(),
        pos[arr[i]].emplace_back(i), loc[i] = pos[arr[i]].size() - 1;

    for (int i = 1; i <= num; i++)
    {
        int tims = 0;
        for (int j = i; j <= num; j++)
        {
            for (int k = st[j]; k <= ed[j]; k++)
                tims = max(tims, ++cnt[arr[k]]);
            f[i][j] = tims;
        }
        memset(cnt, 0, sizeof cnt);
    }

    for (int l, r, lst = 0; m--;)
    {
        cin >> l >> r;
        l ^= lst, r ^= lst;
        cout << (lst = query(l, r)) << '\n';
    }
    return 0;
}