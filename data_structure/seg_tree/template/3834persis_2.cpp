#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int n, m, arr[N];
int rt[N], idx;
struct
{
    int ls, rs, val;
} t[N << 5];

void build(int &p, int l, int r)
// 没初始化数据，啥也没干，简单来说，就连了个边
{
    p = ++idx;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(t[p].ls, l, mid);
    build(t[p].rs, mid + 1, r);
}
int pos;
void update(int &p, int l, int r)
{
    t[++idx] = t[p], t[p = idx].val++;
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(t[p].ls, l, mid);
    else
        update(t[p].rs, mid + 1, r);
}
int query(int o, int p, int l, int r) // 值是通过o树、p树相减得到滴（喜
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1,
        val = t[t[p].ls].val - t[t[o].ls].val;
    if (pos <= val)
        return query(t[o].ls, t[p].ls, l, mid);
    else
        return pos -= val, query(t[o].rs, t[p].rs, mid + 1, r);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    vector<int> nums(arr + 1, arr + n + 1);
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    int len = nums.size();
    build(rt[0], 1, len);
    for (int i = 1; i <= n; i++)
        pos = lower_bound(nums.begin(), nums.end(), arr[i]) - nums.begin() + 1,
        update(rt[i] = rt[i - 1], 1, len);
 
    for (int l, r; m--;)
    {
        cin >> l >> r >> pos;
        cout << nums[query(rt[l - 1], rt[r], 1, len) - 1] << '\n';
    }
    return 0;
}