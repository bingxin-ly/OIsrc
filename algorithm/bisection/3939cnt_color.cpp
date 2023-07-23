#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3e5 + 5;
int n, m, a[N];
vector<int> b[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i], b[a[i]].emplace_back(i);
    for (int i = 1; i <= n; i++)
        sort(b[i].begin(), b[i].end());
    for (int op, l, r, c, x; m--;)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> l >> r >> c;
            cout << upper_bound(b[c].begin(), b[c].end(), r) - lower_bound(b[c].begin(), b[c].end(), l) << '\n';
        }
        else
        {
            cin >> x;
            if (a[x] != a[x + 1])
            {
                *lower_bound(b[a[x]].begin(), b[a[x]].end(), x) += 1;
                *lower_bound(b[a[x + 1]].begin(), b[a[x + 1]].end(), x + 1) -= 1;
                swap(a[x], a[x + 1]);
            }
        }
    }
    return 0;
}