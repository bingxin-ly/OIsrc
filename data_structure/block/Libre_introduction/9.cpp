#include <bits/stdc++.h>
using namespace std;

// 核心维护两个东西
// f[i][j]: 存块 i 到块 j 所有数的最小众数
// vector数组 pos: pos[x] 表示 x 在原数组中依次出现的位置
// pos的替换: 用 s[x][y] 表示前 x 个块中有几个 y
const int N = 1e5 + 10, K = 1300; // 块的个数: n / sqrt(n / log2(n)) 的上界！！！
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
            mode = f[sid + 1][eid - 1], tims = tmp;
        else if (tmp == tims)
            mode = min(mode, f[sid + 1][eid - 1]);
    }
    return mode;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    int len = sqrt(n / log2(n)), num = (n - 1) / len + 1;
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

    for (int l, r; n--;)
    {
        cin >> l >> r;
        cout << val[query(l, r)] << '\n';
    }
    return 0;
}