#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int n, fa[N], sz[N];
int find(int x, int &cnt)
{
    if (fa[x] == x)
        return x;
    int tmp = find(fa[x], cnt);
    sz[x] += sz[fa[x]];
    fa[x] = tmp;
    cnt = sz[x] + 1;
    return fa[x];
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    iota(fa + 1, fa + n + 1, 1);
    int ans = 0x3f3f3f3f;
    for (int i = 1, f, cnt; i <= n; i++)
    {
        cin >> f, cnt = 0;
        if (find(f, cnt) == i)
            ans = min(ans, cnt);
        else
            sz[i] = 1, fa[i] = f;
    }
    cout << ans;
    return 0;
}