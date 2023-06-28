#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5, M = 5e5 + 5;
int n, m, s, k;
struct
{
    int u, v, w;
    bool c;
} a[M], b[M], c[M];
int sza, szb;

int fa[N];
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline bool merge(int x, int y)
{
    x = find(x), y = find(y);
    return x != y && (fa[x] = y);
}

auto cmp = [](const auto &x, const auto &y)
{ return x.w < y.w || (!(y.w < x.w) && x.c > y.c); };
void merge_sort(int x)
{
    for (int i = 1; i <= szb; i++)
        b[i].w += x;
    int i, j, o;
    i = j = o = 0;
    while (i < sza && j < szb)
        if (cmp(a[i + 1], b[j + 1]))
            c[++o] = a[++i];
        else
            c[++o] = b[++j];
    while (i < sza)
        c[++o] = a[++i];
    while (j < szb)
        c[++o] = b[++j];
    for (int i = 1; i <= szb; i++)
        b[i].w -= x;
}
long long cnt, ans;
bool check(int x)
{
    merge_sort(x);
    cnt = ans = 0;
    iota(fa + 1, fa + n + 1, 1);
    int blo = n;
    for (int i = 1; i <= m; i++)
    {
        if (!merge(c[i].u, c[i].v))
            continue;
        cnt += c[i].c, ans += c[i].w;
        if (--blo == 1)
            break;
    }
    return cnt >= k;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> s >> k;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        cin >> u >> v >> w;
        if (u == s || v == s)
            b[++szb] = {u, v, w, true};
        else
            a[++sza] = {u, v, w, false};
    }
    if (szb < k)
        cout << "Impossible", exit(0);

    int blo = n;
    iota(fa + 1, fa + n + 1, 1);
    for (int i = 1; i <= sza; i++)
        blo -= merge(a[i].u, a[i].v);
    for (int i = 1; i <= szb; i++)
        blo -= merge(b[i].u, b[i].v);
    if (blo != 1)
        cout << "Impossible", exit(0);

    sort(a + 1, a + sza + 1, cmp), sort(b + 1, b + szb + 1, cmp);

    int l = -1e9, r = 1e9, maxn = -1e9;
    if (check(r), cnt > k)
        cout << "Impossible", exit(0);
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        check(mid) ? (maxn = max(maxn, mid), l = mid + 1) : (r = mid - 1);
    }
    check(maxn);
    cout << (ans - 1ll * k * maxn);
    return 0;
}