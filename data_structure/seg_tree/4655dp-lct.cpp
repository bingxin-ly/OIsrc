#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, M = 1e6 + 5;
int n, h[N];
long long w[N], f[N];
struct line
{
    long long k, b;
    line(long long k_ = 0, long long b_ = 0x3f3f3f3f3f3f3f3fll) : k(k_), b(b_) {}
} t[M << 2];
inline long long calc(line l, int x) { return l.k * x + l.b; }

#define ls (p << 1)
#define rs (p << 1 | 1)
void update(int p, int l, int r, line ln)
{
    int mid = (l + r) >> 1;
    if (calc(ln, mid) < calc(t[p], mid))
        swap(t[p], ln);
    if (calc(ln, l) < calc(t[p], l))
        update(ls, l, mid, ln);
    if (calc(ln, r) < calc(t[p], r))
        update(rs, mid + 1, r, ln);
}
long long query(int p, int l, int r, int x)
{
    long long ret = calc(t[p], x);
    if (l == r)
        return ret;
    int mid = (l + r) >> 1;
    if (x <= mid)
        ret = min(ret, query(ls, l, mid, x));
    else
        ret = min(ret, query(rs, mid + 1, r, x));
    return ret;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    for (int i = 1; i <= n; i++)
        cin >> w[i], w[i] += w[i - 1];
    f[1] = 0, update(1, 0, 1e6, {-2ll * h[1], 1ll * h[1] * h[1] - w[1]});
    for (int i = 2; i <= n; i++)
    {
        f[i] = 1ll * h[i] * h[i] + w[i - 1] + query(1, 0, 1e6, h[i]);
        update(1, 0, 1e6, {-2ll * h[i], f[i] + 1ll * h[i] * h[i] - w[i]});
    }
    cout << f[n];
    return 0;
}