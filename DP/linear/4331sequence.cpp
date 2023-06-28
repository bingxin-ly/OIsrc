#include <bits/stdc++.h>
using namespace std;

int a[1000005], b[1000005];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], a[i] -= i;
    long long ans = 0;
    priority_queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        q.emplace(a[i]);
        if (a[i] < q.top())
        {
            ans += q.top() - a[i];
            q.emplace(a[i]), q.pop();
        }
        b[i] = q.top();
    }
    for (int i = n - 1; i >= 1; i--)
        b[i] = min(b[i], b[i + 1]);
    cout << ans << '\n';
    for (int i = 1; i <= n; i++)
        cout << b[i] + i << ' ';
    return 0;
}