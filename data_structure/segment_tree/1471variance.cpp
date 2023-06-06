#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
double sum[N << 2], squ[N << 2], tag[N << 2], src[N];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p)
{
    sum[p] = sum[ls] + sum[rs];
    squ[p] = squ[ls] + squ[rs];
}
void pushdown(int p, int l, int r)
{
    // if (abs(tag[p]) > 1e-8) // 不知道要不要确定精度
    if (tag[p])
    {
        int mid = (l + r) >> 1;
        int llen = mid - l + 1, rlen = r - mid;

        squ[ls] += 2 * tag[p] * sum[ls] + llen * tag[p] * tag[p];
        squ[rs] += 2 * tag[p] * sum[rs] + rlen * tag[p] * tag[p];
        sum[ls] += llen * tag[p], sum[rs] += rlen * tag[p];

        tag[ls] += tag[p], tag[rs] += tag[p];
        tag[p] = 0;
    }
}

void build(int p, int l, int r)
{
    if (l == r)
        return sum[p] = src[l], squ[p] = src[l] * src[l], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    pushup(p);
}
void update(int p, int l, int r, int ql, int qr, double v)
{
    if (ql <= l && r <= qr)
    {
        squ[p] += 2 * v * sum[p] + (r - l + 1) * v * v;
        sum[p] += (r - l + 1) * v;
        tag[p] += v;
        return;
    }

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ls, l, mid, ql, qr, v);
    if (qr > mid)
        update(rs, mid + 1, r, ql, qr, v);
    pushup(p);
}
double query(int p, int l, int r, int ql, int qr, bool isum)
{
    if (ql <= l && r <= qr)
        return isum ? sum[p] : squ[p];

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    double res = 0;
    if (ql <= mid)
        res += query(ls, l, mid, ql, qr, isum);
    if (qr > mid)
        res += query(rs, mid + 1, r, ql, qr, isum);
    pushup(p);
    return res;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lf", src + i);
    build(1, 1, n);

    double k;
    for (int opt, x, y; m--;)
    {
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            scanf("%lf", &k), update(1, 1, n, x, y, k);
        else
        {
            int len = y - x + 1;
            double s = query(1, 1, n, x, y, true), avg = s / len;
            if (opt == 2)
                printf("%.4f\n", avg);
            else
            {
                double p = query(1, 1, n, x, y, false),
                       ans = p - 2 * avg * s + len * avg * avg;
                printf("%.4f\n", ans / len);
            }
        }
    }
    return 0;
}