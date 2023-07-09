#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#ifndef ONLINE_JUDGE
ifstream fin("C:\\OIsrc\\.in");
ofstream fout("C:\\OIsrc\\.out");
#define cin fin
#define cout fout
#undef endl
#endif

constexpr int N = 2.5e5 + 5;
int a[N], b[N];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    priority_queue<pair<long long, int>> q;
    long long lst = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        lst += a[i];
        if (lst >= b[i])
            q.emplace(b[i], i), lst -= b[i], ans += 1;
        else if (!q.empty() && q.top().first > b[i])
            lst += q.top().first - b[i], q.pop(), q.emplace(b[i], i);
    }
    cout << ans << '\n';
    vector<int> vec;
    while (!q.empty())
        vec.emplace_back(q.top().second), q.pop();
    sort(vec.begin(), vec.end());
    for (auto i : vec)
        cout << i << ' ';
    return 0;
}