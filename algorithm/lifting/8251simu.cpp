#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e5 + 5;
int n, q;
struct P
{
    int a, b;
} a[N];
int p, nxt[20][N];
pair<P, int> s[N];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i].a;
    for (int i = 1; i <= n; i++)
        cin >> a[i].b;
    for (int i = 1; i <= n; i++)
    {
        while (p && (s[p].first.a == a[i].a || s[p].first.b <= a[i].b))
            nxt[0][s[p--].second] = i;
        s[++p] = {a[i], i};
    }
    for (int i = 1; i <= __lg(n); i++)
        for (int j = 1; j <= n; j++)
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
    for (int l, r; q--;)
    {
        cin >> l >> r;
        int cnt = 0;
        for (int i = __lg(r - l + 1); i >= 0; i--)
            if (nxt[i][l] && nxt[i][l] <= r)
                cnt += 1 << i, l = nxt[i][l];
        cout << cnt + 1 << '\n';
    }
    return 0;
}