#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 10;
int n, m, avai[N], diff[N], need[N];
int d[N], s[N], t[N];

bool check(int num)
{
    memset(diff, 0, sizeof(diff));
    for (int i = 1; i <= num; i++)
        diff[s[i]] += d[i], diff[t[i] + 1] -= d[i];
    for (int i = 1; i <= n; i++)
    {
        need[i] = need[i - 1] + diff[i];
        if (need[i] > avai[i])
            return false;
    }
    return true;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++)
        cin >> x, avai[i] = x;
    for (int i = 1; i <= m; i++)
        cin >> d[i] >> s[i] >> t[i];

    int l = 0, r = N;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid;
    }
    cout << (l > n ? "0" : "-1\n" + to_string(l));
    return 0;
}