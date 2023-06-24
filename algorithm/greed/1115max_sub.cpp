#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int ans = ~0x7fffffff, now = 0;
    istream_iterator<int> in(cin), eof;
    vector<int> val(++in, eof);
    for (auto i : val)
        now += i, ans = max(ans, now), now = max(now, 0);
    cout << ans;
    return 0;
}