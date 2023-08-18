#include <bits/stdc++.h>
using namespace std;

int n, m, q;
unordered_map<int, pair<int, int>> raw, col;
void solve()
{
    raw.clear(), col.clear();
    cin >> n >> m >> q;
    for (int i = 1, op, x, c; i <= q; i++)
    {
        cin >> op >> x >> c;
        if (!op)
            raw[x] = {i, c};
        else
            col[x] = {i, c};
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cout << max(raw[i], col[j]).second << ' ';
        cout << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}