#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m, w[N], cnt[N];
long long res, ans[N];
struct query
{
    int id, l, r;
} q[N];
vector<int> nums;
inline void add(int x) { cnt[x] += 1, res = max(res, 1ll * cnt[x] * nums[x]); }

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    int len = sqrt(n);
    for (int i = 1; i <= n; i++)
        cin >> w[i], nums.emplace_back(w[i]);
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 1; i <= n; i++)
        w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();

    for (int i = 1; i <= m; i++)
        q[i].id = i, cin >> q[i].l >> q[i].r;
    sort(q + 1, q + m + 1, [len](const query &x, const query &y)
         {  int i = x.l / len, j = y.l / len;
            return i < j || (!(j < i) && x.r < y.r); });

    for (int x = 1; x <= m;)
    {
        int y = x;
        while (y <= m && q[y].l / len == q[x].l / len)
            y += 1;
        int r = q[x].l / len * len + len - 1;

        // 暴力块内
        while (x < y && q[x].r <= r)
        {
            for (int k = q[x].l; k <= q[x].r; k++)
                add(w[k]);
            ans[q[x].id] = res;

            // clear
            for (int k = q[x].l; k <= q[x].r; k++)
                cnt[w[k]] -= 1;
            res = 0;
            x += 1;
        }

        // 块外
        res = 0;
        int i = r, j = r + 1;
        while (x < y)
        {
            while (i < q[x].r)
                add(w[++i]);
            long long bac = res;
            while (j > q[x].l)
                add(w[--j]);
            ans[q[x].id] = res;

            // rollback
            while (j <= r)
                cnt[w[j++]] -= 1;
            res = bac;
            x += 1;
        }
        memset(cnt, 0, sizeof cnt);
    }

    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
    return 0;
}