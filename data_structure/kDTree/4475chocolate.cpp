#include <bits/stdc++.h>
using namespace std;

inline void ckmax(int &x, int y) { x = x > y ? x : y; }
inline void ckmin(int &x, int y) { x = x < y ? x : y; }
inline long long squ(long long $) { return $ * $; }
constexpr int N = 5e4 + 5;
struct poi
{
    int ls, rs, val;
    long long sum;
    int di[2], mx[2], mn[2];
} p[N], t[N];

void pushup(int p)
{
    int ls = t[p].ls, rs = t[p].rs;
    for (int i = 0; i <= 1; i++)
    {
        t[p].mn[i] = t[p].mx[i] = t[p].di[i];
        if (ls)
            ckmin(t[p].mn[i], t[ls].mn[i]),
                ckmax(t[p].mx[i], t[ls].mx[i]);
        if (rs)
            ckmin(t[p].mn[i], t[rs].mn[i]),
                ckmax(t[p].mx[i], t[rs].mx[i]);
    }
    t[p].sum = t[ls].sum + t[rs].sum + t[p].val;
}
int build(int l, int r)
{
    int mid = (l + r) >> 1;
    double av1 = 0, av2 = 0, va1 = 0, va2 = 0;
    for (int i = l; i <= r; i++)
        av1 += p[i].di[0], av2 += p[i].di[1];
    av1 /= r - l + 1, av2 /= r - l + 1;
    for (int i = l; i <= r; i++)
        va1 += squ(av1 - p[i].di[0]), va2 += squ(av2 - p[i].di[1]);
    nth_element(p + l, p + mid, p + r + 1, [d = va1 < va2](const poi &x, const poi &y)
                { return x.di[d] < y.di[d]; });
    t[mid] = p[mid];
    if (l < mid)
        t[mid].ls = build(l, mid - 1);
    if (r > mid)
        t[mid].rs = build(mid + 1, r);
    pushup(mid);
    return mid;
}
int a, b, c;
inline bool check(long long x, long long y) { return a * x + b * y < c; }
long long query(int p)
{
    int cnt = 0;
    cnt += check(t[p].mx[0], t[p].mx[1]);
    cnt += check(t[p].mn[0], t[p].mx[1]);
    cnt += check(t[p].mx[0], t[p].mn[1]);
    cnt += check(t[p].mn[0], t[p].mn[1]);
    if (cnt == 4)
        return t[p].sum;
    else if (cnt == 0)
        return 0;

    long long res = 0;
    if (check(t[p].di[0], t[p].di[1]))
        res += t[p].val;
    if (t[p].ls)
        res += query(t[p].ls);
    if (t[p].rs)
        res += query(t[p].rs);
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> p[i].di[0] >> p[i].di[1] >> p[i].val;
    int rt = build(1, n);
    while (m--)
    {
        cin >> a >> b >> c;
        cout << query(rt) << '\n';
    }
    return 0;
}