#include <bits/stdc++.h>
using namespace std;

const int N = 2e5, S = 1e6 + 5;
int n, m, len, res;
int w[N], cnt[S], ans[N];
struct query
{
    int id, l, r, t;
} q[N];
struct change
{
    int p, c;
} c[N];
inline int pos(int $) { return ($ - 1) / len + 1; }
inline void add(int x) { res += !cnt[x], cnt[x] += 1; }
inline void del(int x) { cnt[x] -= 1, res -= !cnt[x]; }

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    int mq = 0, mc = 0;
    for (int i = 1, a, b; i <= m; i++)
    {
        char op;
        cin >> op >> a >> b;
        if (op == 'Q')
            mq += 1, q[mq] = {mq, a, b, mc};
        else
            mc += 1, c[mc] = {a, b};
        // 你要知道，我们修改并不排序，本身就与时间直接联系
    }

    len = pow(n, 2.0 / 3); // 实际操作中还是推荐设定 n^(2/3) 为块长……
    sort(q + 1, q + mq + 1, [](const query &x, const query &y)
         {  int xl = pos(x.l), xr = pos(x.r), yl = pos(y.l), yr = pos(y.r);
            return xl < yl || (!(yl < xl) && (xr < yr || (!(yr < xr) && x.t < y.t))); });

    int ir = 0, il = 1, it = 0;
    for (int k = 1; k <= mq; k++)
    {
        int l = q[k].l, r = q[k].r, t = q[k].t;
        while (ir < r)
            add(w[++ir]);
        while (ir > r)
            del(w[ir--]);
        while (il < l)
            del(w[il++]);
        while (il > l)
            add(w[--il]);
        while (it < t)
        {
            it += 1;
            if (c[it].p >= il && c[it].p <= ir)
                del(w[c[it].p]), add(c[it].c);
            swap(w[c[it].p], c[it].c);
        }
        while (it > t)
        {
            if (c[it].p >= il && c[it].p <= ir)
                del(w[c[it].p]), add(c[it].c);
            swap(w[c[it].p], c[it].c);
            it -= 1;
        }
        ans[q[k].id] = res;
    }

    for (int i = 1; i <= mq; i++)
        cout << ans[i] << '\n';
    return 0;
}