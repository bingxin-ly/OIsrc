#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int n, sum, mxn;
pair<int, int> p[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].first >> p[i].second, sum += p[i].second;
    sort(p + 1, p + n + 1);
    int cnt = 0;
    priority_queue<int, vector<int>, greater<>> q;
    for (int i = n; i >= 1; i--)
    {
        cnt += p[i].second, q.emplace(p[i].second);
        if (n - q.size() < p[i].first)
            cnt -= q.top(), q.pop();
        mxn = max(mxn, cnt);
    }
    cout << sum - mxn;
    return 0;
}