// 60pts
#include <bits/stdc++.h>
#define ls (rt << 1)
#define rs ((rt << 1) | 1)
#define max(_a, _b) ((_a > _b) ? _a : _b)
using namespace std;

const int N = 1e5 + 10;
namespace Maker
{
    unsigned int x0, seed;
    void init() { scanf("%u%u", &x0, &seed); }
    inline unsigned int getnum()
    {
        x0 = (x0 << 3) ^ x0;
        x0 = ((x0 >> 5) + seed) ^ x0;
        return x0;
    }
}
unsigned n, m, arr[N];
unsigned segtr[4 * N];
inline void pushdown(int rt)
{
    segtr[ls] = max(segtr[ls], segtr[rt]);
    segtr[rs] = max(segtr[rs], segtr[rt]);
}
unsigned query(int rt, int l, int r, const int pos)
{
    if (l == r)
        return segtr[rt];

    pushdown(rt);
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return query(ls, l, mid, pos);
    else
        return query(rs, mid + 1, r, pos);
}
void cover(int rt, int l, int r, const int ll, const int rr, const int val)
{
    if (l > rr || r < ll)
        return;
    if (ll <= l && r <= rr)
        return segtr[rt] = max(segtr[rt], val), void();

    int mid = (l + r) >> 1;
    if (l <= mid)
        cover(ls, l, mid, ll, rr, val);
    if (r > mid)
        cover(rs, mid + 1, r, ll, rr, val);
}

int main()
{
    int typ;
    scanf("%d%d%d", &n, &m, &typ);
    for (int i = 1; i <= n; i++)
        scanf("%u", &arr[i]);

    Maker::init();
    for (int i = 1; i <= m; ++i)
    {
        int l = Maker::getnum() % n + 1, r = Maker::getnum() % n + 1;
        unsigned int v = Maker::getnum();
        if (l > r)
            swap(l, r);
        if (typ == 1)
            l = 1;

        cover(1, 1, n, l, r, v);
    }
    for (int i = 1; i <= n; i++)
        printf("%u ", max(arr[i], query(1, 1, n, i)));
    return 0;
}
