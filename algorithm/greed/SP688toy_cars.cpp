#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 5e5 + 5;
int seq[N], len[N], pos[N];

void solve()
{
    int n, k, p;
    cin >> n >> k >> p;
    for (int i = 1; i <= p; i++)
        cin >> seq[i];
    fill(pos + 1, pos + n + 1, p + 1);
    for (int i = p; i >= 1; i--)
        len[i] = pos[seq[i]], pos[seq[i]] = i;
    priority_queue<pair<int, int>> q;
    set<int> s;
    int cnt = 0;
    for (int i = 1; i <= p; i++)
    {
        if (s.count(seq[i]))
        {
            k += 1;
            q.emplace(len[i], seq[i]);
        }
        else if (q.size() < (size_t)k)
            cnt += 1, s.insert(seq[i]), q.emplace(len[i], seq[i]);
        else
        {
            s.erase(s.lower_bound(q.top().second)), q.pop();
            cnt += 1, s.insert(seq[i]), q.emplace(len[i], seq[i]);
        }
    }
    cout << cnt << endl;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}