#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\.in");
ofstream fout("D:\\OIsrc\\.out");
#define cin fin
#define cout fout
#endif

const int N = 1e5 + 5, K = 2e5 + 5;
int n, k, res[N];
namespace BIT
{
    int t[K];
    inline int lowbit(int x) { return x & -x; }
    void add(int p, int v)
    {
        for (; p <= k; p += lowbit(p))
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
struct ele
{
    int a, b, c;
    int cnt, res;
    bool operator!=(const ele &o) const { return a != o.a || b != o.b || c != o.c; }
} a[N], b[N];

auto cmp = [](const ele &x, const ele &y)
{ return x.b < y.b || (!(y.b < x.b) && x.c < y.c); };
void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    sort(b + l, b + mid + 1, cmp), sort(b + mid + 1, b + r + 1, cmp);
    int i = l, j = mid + 1; // 两个指针，指向左右段初始的位置
    while (j <= r)
    {
        while (i <= mid && b[i].b <= b[j].b)
            BIT::add(b[i].c, b[i].cnt), i++;
        b[j].res += BIT::ask(b[j].c), j++;
    }
    for (int k = l; k < i; k++)
        BIT::add(b[k].c, -b[k].cnt);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i].a >> a[i].b >> a[i].c;
    sort(a + 1, a + n + 1, [](const ele &x, const ele &y)
         { return x.a < y.a || (!(y.a < x.a) && (x.b < y.b || (!(y.b < x.b) && x.c < y.c))); });
    int m = 0;
    for (int i = 1, t = 0; i <= n; i++)
    {
        t += 1;
        if (a[i] != a[i + 1])
        {
            m += 1;
            b[m] = a[i], b[m].cnt = t;
            t = 0;
        }
    }
    cdq(1, m);
    for (int i = 1; i <= m; i++)
        res[b[i].res + b[i].cnt] += b[i].cnt;
    for (int i = 1; i <= n; i++)
        cout << res[i] << '\n';
    return 0;
}