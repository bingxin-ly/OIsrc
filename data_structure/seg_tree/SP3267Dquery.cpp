#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e4 + 5;
struct
{
    int ls, rs, val;
} t[N << 5];
int n, m, arr[N];
int idx, rt[N], lst[N];

void update(int &p, int l, int r, int pos, int val)
{
    t[++idx] = t[p], p = idx;
    if (l == r)
        return t[p].val += val, void();
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(t[p].ls, l, mid, pos, val);
    else
        update(t[p].rs, mid + 1, r, pos, val);
    t[p].val = t[t[p].ls].val + t[t[p].rs].val;
}
int query(int p, int l, int r, int pos)
{
    if (l == r)
        return t[p].val;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return t[t[p].rs].val + query(t[p].ls, l, mid, pos);
    else
        return query(t[p].rs, mid + 1, r, pos);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    vector<int> nums(arr + 1, arr + n + 1);
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 1; i <= n; i++)
    {
        arr[i] = lower_bound(nums.begin(), nums.end(), arr[i]) - nums.begin() + 1;
        rt[i] = rt[i - 1];
        if (lst[arr[i]])
            update(rt[i], 1, n, lst[arr[i]], -1);
        update(rt[i], 1, n, lst[arr[i]] = i, 1);
    }

    cin >> m;
    int l, r;
    while (m--)
    {
        cin >> l >> r;
        cout << query(rt[r], 1, n, l) << '\n';
    }
    return 0;
}