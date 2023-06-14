#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10;
int tr[N << 2], tag[N << 2];

#define ls (p << 1)
#define rs (p << 1 | 1)
void pushup(int p)
{
    tr[p] = tr[ls] + tr[rs];
}
void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        int mid = (l + r) >> 1;
        if (tag[p] == 2)
            tr[ls] = mid - l + 1, tr[rs] = r - mid;
        else
            tr[ls] = tr[rs] = 0;

        tag[ls] = tag[rs] = tag[p];
        tag[p] = 0;
    }
}

void update(int p, int l, int r, int ql, int qr, bool type)
{
    if (ql <= l && r <= qr)
        return tr[p] = (r - l + 1) * type, tag[p] = type + 1, void();

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ls, l, mid, ql, qr, type);
    if (qr > mid)
        update(rs, mid + 1, r, ql, qr, type);
    pushup(p);
}
int query(int p, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return tr[p];

    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid)
        res += query(ls, l, mid, ql, qr);
    if (qr > mid)
        res += query(rs, mid + 1, r, ql, qr);
    pushup(p);
    return res;
}

int n;
int bin_search(int x, int num)
{
    int l = x, r = n, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if ((mid - x + 1) - query(1, 1, n, x, mid) >= num)
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
#endif
    int t, m;
    scanf("%d", &t);
    while (t--)
    {
        memset(tr, 0, sizeof tr), memset(tag, 0, sizeof tag);
        scanf("%d%d", &n, &m);
        for (int opt, x, y; m--;)
        {
            scanf("%d%d%d", &opt, &x, &y);
            x += 1, y += 1;
            if (opt == 1)
            {
                int cnt = (n - x + 1) - query(1, 1, n, x, n);
                if (cnt == 0)
                {
                    puts("Can not put any one.");
                    continue;
                }
                int l = bin_search(x, 1), r = bin_search(x, min(y - 1, cnt));
                update(1, 1, n, l, r, 1);
                printf("%d %d\n", l - 1, r - 1);
            }
            else
                printf("%d\n", query(1, 1, n, x, y)), update(1, 1, n, x, y, 0);
        }
        putchar('\n');
    }
    return 0;
}