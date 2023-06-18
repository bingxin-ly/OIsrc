#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> num;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        unordered_map<int, int> fac;
        for (int j = 2, up = sqrt(x); j <= up; j++)
            while (!(x % j))
                ++fac[j], x /= j;
        if (x != 1)
            ++fac[x];
        for (const auto &j : fac)
            num[j.first] += j.second;
    }

    int ans = 0;
    for (auto i : num)
    {
        int l = 1, r = 1e8;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            long long now = i.first, cnt = 0;
            while (now <= mid)
            {
                cnt += mid / now;
                now *= i.first;
            }
            if (cnt < i.second)
                l = mid + 1;
            else
                r = mid;
        }
        ans = max(ans, l);
    }
    cout << ans;
    return 0;
}