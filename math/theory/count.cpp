#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int n, m, top, ans;
vector<int> fac;
void dfs(vector<int> s)
{
    if ((int)s.size() == m << 1)
    {
        int cnt = 1;
        for (int i : s)
            if ((cnt *= i) > top)
                return;
        (ans += 1) %= 998244353;
        return;
    }
    for (int i : fac)
    {
        auto t = s;
        t.emplace_back(i);
        dfs(t);
    }
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    top = pow(n, m);
    for (int i = 1, up = sqrt(n); i <= up; i++)
        if (!(n % i))
        {
            fac.emplace_back(i);
            if (i * i != n)
                fac.emplace_back(n / i);
        }
    dfs(vector<int>());
    cout << ans;
    return 0;
}