#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1.5e5 + 5;
int n, f[N];
struct grass
{
    int s, t, v;
} a[N];

int bins(int l, int r, int k)
{
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (a[mid].t < k)
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].s >> a[i].t, a[i].v = a[i].t - a[i].s + 1;
    sort(a + 1, a + n + 1, [](grass a, grass b)
         { return a.t < b.t; });
    for (int i = 1; i <= n; i++)
        f[i] = max(f[i - 1], f[bins(0, i - 1, a[i].s)] + a[i].v);
    cout << f[n];
    return 0;
}