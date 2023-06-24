#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 5;
int n, m, k;
int u[N], v[N], w[N];
bool c[N];

int f[N];
inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

struct
{
    int u, v, w;
    bool c;
} e[N];
int cnt, ans;
void check(int x)
{
    cnt = ans = 0;
    for (int i = 1; i <= m; i++)
        e[i] = {u[i], v[i], w[i] - x * !c[i], c[i]};
    sort(e + 1, e + m + 1, [](const auto &x, const auto &y)
         { return x.w < y.w || (!(y.w < x.w) && x.c < y.c); });
    iota(f, f + n, 0);
    for (int i = 1; i <= m; i++)
    {
        int fu = find(e[i].u), fv = find(e[i].v);
        if (fu == fv)
            continue;
        f[fv] = fu;
        cnt += !e[i].c, ans += e[i].w;
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
        cin >> u[i] >> v[i] >> w[i] >> c[i];

    int l = -100, r = 100;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        check(mid);
        if (cnt >= k)
            r = mid;
        else
            l = mid + 1;
    }
    check(l);
    cout << (ans + l * k);
    return 0;
}