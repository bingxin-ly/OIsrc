#include <bits/stdc++.h>
using namespace std;

const int maxn = 200010;
int n, op, xl, xr, yl, yr, lstans;

struct node
{
    int x, y, v;
} s[maxn];

bool cmp1(int a, int b) { return s[a].x < s[b].x; }

bool cmp2(int a, int b) { return s[a].y < s[b].y; }

double a = 0.725;
int rt, cur, d[maxn], ls[maxn], rs[maxn], L[maxn], R[maxn], D[maxn], U[maxn],
    siz[maxn], sum[maxn];
int g[maxn], tot;


void maintain(int u)
{
    siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
    sum[u] = sum[ls[u]] + sum[rs[u]] + s[u].v;
    L[u] = R[u] = s[u].x;
    D[u] = U[u] = s[u].y;
    if (ls[u])
        L[u] = min(L[u], L[ls[u]]), R[u] = max(R[u], R[ls[u]]),
        D[u] = min(D[u], D[ls[u]]), U[u] = max(U[u], U[ls[u]]);
    if (rs[u])
        L[u] = min(L[u], L[rs[u]]), R[u] = max(R[u], R[rs[u]]),
        D[u] = min(D[u], D[rs[u]]), U[u] = max(U[u], U[rs[u]]);
}
int build(int l, int r)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    double av1 = 0, av2 = 0, va1 = 0, va2 = 0;
    for (int i = l; i <= r; i++)
        av1 += s[g[i]].x, av2 += s[g[i]].y;
    av1 /= (r - l + 1), av2 /= (r - l + 1);
    for (int i = l; i <= r; i++)
        va1 += (av1 - s[g[i]].x) * (av1 - s[g[i]].x),
            va2 += (av2 - s[g[i]].y) * (av2 - s[g[i]].y);
    if (va1 > va2)
        nth_element(g + l, g + mid, g + r + 1, cmp1), d[g[mid]] = 1;
    else
        nth_element(g + l, g + mid, g + r + 1, cmp2), d[g[mid]] = 0;
    ls[g[mid]] = build(l, mid - 1);
    rs[g[mid]] = build(mid + 1, r);
    maintain(g[mid]);
    return g[mid];
}

void print(int u)
{
    if (!u)
        return;
    print(ls[u]);
    g[++tot] = u;
    print(rs[u]);
}
void rebuild(int &u)
{
    tot = 0;
    print(u);
    u = build(1, tot);
}

bool bad(int u) { return a * siz[u] <= (double)max(siz[ls[u]], siz[rs[u]]); }

void insert(int &u, int v)
{
    if (!u)
    {
        u = v;
        maintain(u);
        return;
    }
    if (d[u] == 1)
    {
        if (s[v].x <= s[u].x)
            insert(ls[u], v);
        else
            insert(rs[u], v);
    }
    else
    {
        if (s[v].y <= s[u].y)
            insert(ls[u], v);
        else
            insert(rs[u], v);
    }
    maintain(u);
    if (bad(u))
        rebuild(u);
}

int query(int u)
{
    if (!u || xr < L[u] || xl > R[u] || yr < D[u] || yl > U[u])
        return 0;
    if (xl <= L[u] && R[u] <= xr && yl <= D[u] && U[u] <= yr)
        return sum[u];
    int ret = 0;
    if (xl <= s[u].x && s[u].x <= xr && yl <= s[u].y && s[u].y <= yr)
        ret += s[u].v;
    return query(ls[u]) + query(rs[u]) + ret;
}

int main()
{
    scanf("%d", &n);
    while (~scanf("%d", &op))
    {
        if (op == 1)
        {
            cur++, scanf("%d%d%d", &s[cur].x, &s[cur].y, &s[cur].v);
            s[cur].x ^= lstans;
            s[cur].y ^= lstans;
            s[cur].v ^= lstans;
            insert(rt, cur);
        }
        if (op == 2)
        {
            scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
            xl ^= lstans;
            yl ^= lstans;
            xr ^= lstans;
            yr ^= lstans;
            printf("%d\n", lstans = query(rt));
        }
        if (op == 3)
            return 0;
    }
}
