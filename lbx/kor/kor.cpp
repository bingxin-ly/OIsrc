#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
int n, k, a[N];
priority_queue<pair<int, vector<int>>> lace;
signed main()
{
    freopen("kor.in", "r", stdin);
    freopen("kor.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vector<int> pil;
    for (int i = 0, cnt; i < 1 << n; i++)
    {
        pil.clear(), cnt = 0;
        for (int j = 0; j < n; j++)
            if (i >> j & 1)
                pil.emplace_back(j + 1), cnt += a[j + 1];
        lace.emplace(-cnt, pil);
    }
    while (--k)
        lace.pop();
    cout << -lace.top().first << '\n';
    for (int i : lace.top().second)
        cout << i << ' ';
    return 0;
}