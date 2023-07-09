#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define endl '\n'

constexpr int N = 5e4 + 5;
long long n, k, m;
struct cow
{
    int p, c;
} s[N];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i].p >> s[i].c;
    sort(s + 1, s + n + 1, [](const cow &a, const cow &b)
         { return a.c < b.c; });
    long long cost = 0;
    priority_queue<pii, vector<pii>, greater<>> pi, ci, di;
    for (int i = 1; i <= k; i++)
    {
        cost += s[i].c, di.emplace(s[i].p - s[i].c, i);
        if (cost > m)
            cout << i - 1, exit(0);
    }
    for (int i = k + 1; i <= n; i++)
        pi.emplace(s[i].p, i), ci.emplace(s[i].c, i);
    for (int i = k + 1; i <= n; i++)
    {
        int v1, v2 = pi.top().first;
        if (!di.empty())
            cost += min(v1 = ci.top().first + di.top().first, v2);
        else
            cost += v2;
        if (cost > m)
            cout << i - 1, exit(0);
        int c1 = ci.top().second, p1 = pi.top().second;
        if (di.empty() || v1 >= v2)
        {
            pi.pop();
            c1 == p1 && (ci.pop(), true);
        }
        else
        {
            di.pop(), ci.pop();
            c1 == p1 && (pi.pop(), true);
        }
    }
    cout << n;
    return 0;
}