#include <bits/stdc++.h>
using namespace std;

constexpr int T = 1e6 + 5;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    static int n, t, nxt[T];
    cin >> n >> t;
    for (int i = 1, l, r; i <= n; i++)
        cin >> l >> r, nxt[l] = max(nxt[l], r);
    for (int i = 1; i <= t; i++)
        nxt[i] = max(nxt[i], nxt[i - 1]);
    int p = 1, c = 0;
    while (p <= t && nxt[p] >= p)
        p = nxt[p] + 1, c++;
    cout << (p <= t ? -1 : c);
    return 0;
}