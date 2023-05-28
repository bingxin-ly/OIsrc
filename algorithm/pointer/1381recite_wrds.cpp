#include <bits/stdc++.h>
using namespace std;

const int M = 1e5 + 10;
int num, len = INT_MAX;
string str, pas[M];
unordered_map<string, bool> recite;
unordered_map<string, int> cnt;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> str, recite[str] = true;
    cin >> m;
    int l = 1;
    for (int r = 1; r <= m; r++)
    {
        cin >> pas[r];
        if (recite[pas[r]])
            cnt[pas[r]]++;
        if (cnt[pas[r]] == 1)
            num++, len = r - l + 1;
        while (l <= r)
        {
            if (!recite[pas[l]])
            {
                l++;
                continue;
            }
            if (cnt[pas[l]] >= 2)
            {
                cnt[pas[l++]]--;
                continue;
            }
            break;
        }
        len = min(len, r - l + 1);
    }
    cout << num << '\n'
         << len;
    return 0;
}
