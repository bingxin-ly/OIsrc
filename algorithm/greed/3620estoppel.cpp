#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int N = 1e5 + 5;
int n, k, ans, s[N], d[N], pre[N], suf[N];
priority_queue<pii, vector<pii>, greater<>> q;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> s[i], d[i] = s[i] - s[i - 1];
    for (int i = 2; i <= n; i++)
        q.emplace(d[i], i), pre[i] = i - 1, suf[i] = i + 1;
    d[1] = 1 << 30, d[n + 1] = 1 << 30;
    while (k --)
    {
        while (q.top().first != d[q.top().second])
            q.pop();
        int val = q.top().first, p = q.top().second, v = 0;
        q.pop(), ans += val;
        v += d[pre[p]], d[pre[p]]=1 << 30, pre[p] = pre[pre[p]], suf[pre[p]] = p;
        v += d[suf[p]], d[suf[p]] =1 << 30, suf[p] = suf[suf[p]], pre[suf[p]] = p;
        d[p] = val = v - val, q.emplace(val, p);
    }
    cout << ans;
    return 0;
}