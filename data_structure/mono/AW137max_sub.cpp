#include <bits/stdc++.h>
#define int long long
using namespace std;

int s[300005];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i], s[i] += s[i - 1];
    int res = LLONG_MIN;
    deque<int> q;
    q.emplace_back(0);
    for (int i = 1; i <= n; i++)
    {
        if (!q.empty() && i - q.front() > m)
            q.pop_front();
        res = max(res, s[i] - s[q.front()]);
        while (!q.empty() && s[q.back()] >= s[i])
            q.pop_back();
        q.emplace_back(i);
    }
    cout << res;
    return 0;
}