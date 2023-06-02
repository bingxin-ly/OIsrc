#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, a[N], val[N];
deque<int> q1, q2;

inline bool cmp(int x, int y)
{
    return val[x] == val[y] ? x < y : val[x] < val[y];
}

bool judge()
{
    if (!q2.empty())
        return true;
    if (q1.size() == 1)
        return true;
    if (q1.size() == 2)
        return false;

    int x = q1.front(), y = q1.back();
    q1.pop_front(), q1.pop_back();
    val[y] -= val[x];

    if (cmp(y, q1.front()))
        return q1.emplace_front(y), !judge();
    else
        return false;
}
bool check()
{
    if (q2.empty())
        return false;

    int x = q1.back(), y = q2.front();
    q1.pop_back(), q2.pop_front();
    val[x] -= val[y];

    while (!q2.empty() && cmp(x, q2.back()))
        q1.emplace_front(q2.back()), q2.pop_back();
    q1.emplace_front(x);
    return judge();
}
void solve()
{
    copy(a + 1, a + n + 1, val + 1);
    q1.clear(), q2.clear();

    for (int i = 1; i < n; i++)
        q2.emplace_back(i);
    q1.emplace_back(n);

    int ans = n;
    while (check())
        ans--;
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T, k;

    cin >> T >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    solve();

    while (--T)
    {
        cin >> k;
        for (int x, y; k--;) // for 还能这么用 666
            cin >> x >> y, a[x] = y;
        solve();
    }
    return 0;
}