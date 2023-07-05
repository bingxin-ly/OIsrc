#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\.in");
ofstream fout("D:\\OIsrc\\.out");
#define cin fin
#define cout fout
#endif

constexpr int N = 1e5 + 5;
int n, m, pos[N];
long long ans[N];
namespace BIT
{
    int t[N];
    inline int lowbit(int x) { return x & -x; }
    void add(int p, int v)
    {
        for (; p <= n; p += lowbit(p))
            t[p] += v;
    }
    int ask(int p)
    {
        int ret = 0;
        for (; p; p -= lowbit(p))
            ret += t[p];
        return ret;
    }
}
struct num
{
    int typ, val, pos, qid;
} a[N << 1];
void cdq(int l, int r)
{
    static auto cmp = [](const num &x, const num &y)
    { return x.pos < y.pos; };
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    sort(a + l, a + mid + 1, cmp), sort(a + mid + 1, a + r + 1, cmp);
    int i = l, j = mid + 1;
    while (j <= r)
    {
        while (i <= mid && a[i].pos <= a[j].pos)
            BIT::add(a[i].val, a[i].typ), i++;
        ans[a[j].qid] += a[j].typ * (BIT::ask(n) - BIT::ask(a[j].val)), j++;
    }
    for (int k = l; k < i; k++)
        BIT::add(a[k].val, -a[k].typ);

    i = mid, j = r; // 从另一个方向扫
    while (j > mid)
    {
        while (i >= l && a[i].pos >= a[j].pos)
            BIT::add(a[i].val, a[i].typ), i--;
        ans[a[j].qid] += a[j].typ * (BIT::ask(a[j].val - 1)), j--;
    }
    for (int k = mid; k > i; k--)
        BIT::add(a[k].val, -a[k].typ);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++)
        cin >> x, pos[x] = i, a[i] = {1, x, i, 0};
    for (int i = 1, x; i <= m; i++)
        cin >> x, a[n + i] = {-1, x, pos[x], i};
    cdq(1, n + m);
    for (int i = 1; i <= m; i++)
        ans[i] += ans[i - 1], cout << ans[i - 1] << '\n';
    return 0;
}