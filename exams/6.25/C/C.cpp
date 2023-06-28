#include <bits/stdc++.h>
using namespace std;

int n, m, pri[40], val[40];
long long t, ans, id;
vector<int> v;
vector<pair<int, long long>> sav;
void proc1()
{
    int resp = 0;
    long long resv = 0;
    for (auto i : v)
        resp ^= pri[i], resv += val[i];
    sav.emplace_back(resp, resv);
}
void proc2()
{
    int resp = 0;
    long long resv = 0;
    for (auto i : v)
        resp ^= pri[i], resv += val[i];
    for (const auto &i : sav)
        if ((resp ^ i.first) <= m)
            ans = max(ans, resv + i.second);
}
void dfs(int x)
{
    if (x == t + 1)
        return !id ? proc1() : proc2();
    v.emplace_back(x), dfs(x + 1), v.pop_back();
    dfs(x + 1);
}

signed main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> pri[i];
    for (int i = 1; i <= n; i++)
        cin >> val[i];

    int half = n >> 1;
    t = half, id = 0;
    dfs(1);

    t = n, id = 1;
    dfs(half + 1);
    cout << ans;
    return 0;
}