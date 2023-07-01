#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, len, w[N];
int res, fst[N], lst[N], ans[N];
struct query
{
    int id, l, r;
} q[N];
vector<int> nums;
inline int pos(int $) { return ($ - 1) / len + 1; }
inline void add1(int x, int p)
{
    if (!fst[x])
        fst[x] = p;
    lst[x] = p;
    res = max(res, lst[x] - fst[x]);
}
inline void add2(int x, int p)
{
    if (!lst[x])
        lst[x] = p;
    res = max(res, lst[x] - p);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    len = sqrt(n);
    for (int i = 1; i <= n; i++)
        cin >> w[i], nums.emplace_back(w[i]);
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (int i = 1; i <= n; i++)
        w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();

    cin >> m;
    for (int i = 1; i <= m; i++)
        q[i].id = i, cin >> q[i].l >> q[i].r;
    sort(q + 1, q + m + 1, [](const query &x, const query &y)
         {  int i = pos(x.l), j = pos(y.l);
            return i < j || (!(j < i) && x.r < y.r); });

    for (int x = 1; x <= m;)
    {
        int y = x;
        while (y <= m && pos(q[y].l) == pos(q[x].l))
            y += 1;
        int r = pos(q[x].l) * len;

        while (x < y && q[x].r <= r)
        {
            for (int k = q[x].l; k <= q[x].r; k++)
                add1(w[k], k);
            ans[q[x].id] = res;

            for (int k = q[x].l; k <= q[x].r; k++)
                fst[w[k]] = lst[w[k]] = 0;
            res = 0;
            x += 1;
        }

        int i = r, j = r + 1;
        while (x < y)
        {
            while (i < q[x].r)
                i += 1, add1(w[i], i);
            int bac = res;
            while (j > q[x].l)
                j -= 1, add2(w[j], j);
            ans[q[x].id] = res;

            // rollback
            while (j <= r)
            {
                if (lst[w[j]] <= r)
                    lst[w[j]] = 0;
                j += 1;
            }
            res = bac;
            x += 1;
        }
        res = 0, memset(fst, 0, sizeof fst), memset(lst, 0, sizeof lst);
    }

    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
    return 0;
}