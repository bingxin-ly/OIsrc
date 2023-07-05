#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 10;
struct
{
    int x, y, v;
} s[N];
double alpha = 0.7;
int ls[N], rs[N], L[N], R[N], D[N], U[N];
int tot, g[N], siz[N], sum[N];
bool d[N];

inline long long squ(long long $) { return $ * $; }
void pushup(int u)
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
    double av1 = 0, av2 = 0, va1 = 0, va2 = 0; // average variance
    for (int i = l; i <= r; i++)
        av1 += s[g[i]].x, av2 += s[g[i]].y;
    av1 /= (r - l + 1), av2 /= (r - l + 1);
    for (int i = l; i <= r; i++)
        va1 += squ(av1 - s[g[i]].x), va2 += squ(av2 - s[g[i]].y);
    d[g[mid]] = va1 > va2;
    nth_element(g + l, g + mid, g + r + 1,
                [va1, va2](const auto &a, const auto &b)
                { return va1 > va2 ? s[a].x < s[b].x : s[a].y < s[b].y; });
    ls[g[mid]] = build(l, mid - 1), rs[g[mid]] = build(mid + 1, r);
    pushup(g[mid]);
    return g[mid];
}
void inorder(int u)
{
    if (!u)
        return;
    inorder(ls[u]), g[++tot] = u, inorder(rs[u]);
}
void rebuild(int &u)
{
    tot = 0, inorder(u);
    u = build(1, tot);
}
void insert(int &u, int v)
{
    if (!u)
        return u = v, pushup(u);

    if (d[u])
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
    pushup(u);
    if (alpha * siz[u] <= max(siz[ls[u]], siz[rs[u]]))
        rebuild(u);
}

int xl, yl, xr, yr;
int query(int u)
{
    if (!u || xl > R[u] || yl > U[u] || xr < L[u] || yr < D[u])
        return 0;
    if (xl <= L[u] && R[u] <= xr && yl <= D[u] && U[u] <= yr)
        return sum[u];
    return query(ls[u]) + query(rs[u]) +
           (xl <= s[u].x && s[u].x <= xr && yl <= s[u].y && s[u].y <= yr ? s[u].v : 0);
}

int rt, cnt, lst;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    while (cin >> n, n != 3)
    {
        if (n == 1)
        {
            cnt++;
            cin >> s[cnt].x >> s[cnt].y >> s[cnt].v;
            s[cnt].x ^= lst, s[cnt].y ^= lst, s[cnt].v ^= lst;
            insert(rt, cnt);
        }
        else
        {
            cin >> xl >> yl >> xr >> yr;
            xl ^= lst, yl ^= lst, xr ^= lst, yr ^= lst;
            cout << (lst = query(rt)) << '\n';
        }
    }
    return 0;
}
