#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 6e5 + 9;
inline int max(int x, int y) { return x > y ? x : y; }
inline int min(int x, int y) { return x < y ? x : y; }

int n, m, w, ans[N >> 1];
vector<int> nums;
struct poi
{
    int x, y, qid;
} p[N];
struct fenwick
{
    int t[N << 2];
    fenwick() { memset(t, ~0x3f, sizeof t); }
    inline int lowbit(int x) { return x & -x; }
    void upd(int p, int x)
    {
        for (; p < w; p += lowbit(p))
            t[p] = max(t[p], x);
    }
    int ask(int p)
    {
        int ret = ~0x3f3f3f3f;
        for (; p; p -= lowbit(p))
            ret = max(ret, t[p]);
        return ret;
    }
    void clear(int p)
    {
        for (; p < w; p += lowbit(p))
            t[p] = ~0x3f3f3f3f;
    }
} b, d;

void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1, id;
    cdq(l, mid);

    vector<poi> seq;
    for (int i = l; i <= mid; i++)
        if (!p[i].qid)
            seq.emplace_back(p[i]);
    for (int i = mid + 1; i <= r; i++)
        if (p[i].qid)
            seq.emplace_back(p[i]);
    sort(seq.begin(), seq.end(), [](const poi &a, const poi &b)
         { return a.x < b.x; });

    for (const auto &o : seq)
        if (!o.qid)
            b.upd(o.y, nums[o.x] + nums[o.y]), d.upd(w - o.y, nums[o.x] - nums[o.y]);
        else
            id = o.qid,
            ans[id] = min(ans[id], nums[o.x] + nums[o.y] - b.ask(o.y)),
            ans[id] = min(ans[id], nums[o.x] - nums[o.y] - d.ask(w - o.y));
    for (const auto &o : seq)
        if (!o.qid)
            b.clear(o.y), d.clear(w - o.y);
    reverse(seq.begin(), seq.end());
    for (const auto &o : seq)
        if (!o.qid)
            b.upd(o.y, nums[o.y] - nums[o.x]), d.upd(w - o.y, -nums[o.x] - nums[o.y]);
        else
            id = o.qid,
            ans[id] = min(ans[id], -nums[o.x] + nums[o.y] - b.ask(o.y)),
            ans[id] = min(ans[id], -nums[o.x] - nums[o.y] - d.ask(w - o.y));
    for (const auto &o : seq)
        if (!o.qid)
            b.clear(o.y), d.clear(w - o.y);

    cdq(mid + 1, r);
}

void discretize()
{
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    w = nums.size() + 1;
    for (int i = 1; i <= n + m; i++)
        p[i].x = lower_bound(nums.begin(), nums.end(), p[i].x) - nums.begin() + 1,
        p[i].y = lower_bound(nums.begin(), nums.end(), p[i].y) - nums.begin() + 1;
    nums.emplace(nums.begin(), 0);
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y,
            nums.emplace_back(p[i].x), nums.emplace_back(p[i].y);
    int q = 0;
    for (int i = 1, op, x, y; i <= m; i++)
    {
        cin >> op >> x >> y;
        nums.emplace_back(x), nums.emplace_back(y);
        p[n + i] = {x, y, op == 1 ? 0 : ++q};
    }
    discretize();

    memset(ans, 0x3f, sizeof ans);
    cdq(1, n + m);

    for (int i = 1; i <= q; i++)
        cout << ans[i] << endl;
    return 0;
}