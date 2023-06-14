#include <bits/stdc++.h>
using namespace std;

// 就是入门 9
const int N = 4e4 + 10, K = 800;
int blo[N], st[K], ed[K];
int arr[N], cnt[N], f[K][K];
vector<int> pos[N];

inline int min(int a, int b) { return a < b ? a : b; }
inline int count(int x, int l, int r)
{
    return upper_bound(pos[x].begin(), pos[x].end(), r) -
           lower_bound(pos[x].begin(), pos[x].end(), l);
}
int query(int l, int r)
{
    int sid = blo[l], eid = blo[r];
    if (sid == eid)
    {
        memset(cnt, 0, sizeof(cnt));
        int mode = INT_MAX, tims = 0;
        for (int i = l; i <= r; i++)
        {
            cnt[arr[i]] += 1;
            if (cnt[arr[i]] > tims)
                mode = arr[i], tims = cnt[arr[i]];
            else if (cnt[arr[i]] == tims)
                mode = min(mode, arr[i]);
        }
        return mode;
    }

    int mode = INT_MAX, tims = 0, tmp;
    for (int i = l; i <= ed[sid]; i++)
    {
        tmp = count(arr[i], l, r);
        if (tmp > tims)
            mode = arr[i], tims = tmp;
        else if (tmp == tims)
            mode = min(mode, arr[i]);
    }
    for (int i = st[eid]; i <= r; i++)
    {
        tmp = count(arr[i], l, r);
        if (tmp > tims)
            mode = arr[i], tims = tmp;
        else if (tmp == tims)
            mode = min(mode, arr[i]);
    }
    if (sid + 1 <= eid - 1)
    {
        tmp = count(f[sid + 1][eid - 1], l, r);
        if (tmp > tims)
            mode = f[sid + 1][eid - 1];
        else if (tmp == tims)
            mode = min(mode, f[sid + 1][eid - 1]);
    }
    return mode;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int len = sqrt(n / log2(n)), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1, ed[i] = i * len;
    ed[num] = n;

    vector<int> val(n);
    for (int i = 1; i <= n; i++)
        blo[i] = (i - 1) / len + 1,
        cin >> arr[i], val[i - 1] = arr[i];
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 1; i <= n; i++)
        arr[i] = lower_bound(val.begin(), val.end(), arr[i]) - val.begin(),
        pos[arr[i]].emplace_back(i);

    for (int i = 1, sz = val.size() << 2; i <= num; i++)
    {
        memset(cnt, 0, sz);
        int mode = INT_MAX, tims = 0;
        for (int j = i; j <= num; j++)
        {
            for (int k = st[j]; k <= ed[j]; k++)
            {
                cnt[arr[k]] += 1;
                if (cnt[arr[k]] > tims)
                    mode = arr[k], tims = cnt[arr[k]];
                else if (cnt[arr[k]] == tims)
                    mode = min(mode, arr[k]);
            }
            f[i][j] = mode;
        }
    }

    for (int l, r, x = 0; m--;)
    {
        cin >> l >> r;
        l = (l + x - 1) % n + 1, r = (r + x - 1) % n + 1;
        if (l > r)
            l ^= r ^= l ^= r;
        cout << (x = val[query(l, r)]) << '\n';
    }
    return 0;
}