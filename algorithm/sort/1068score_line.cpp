#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> scores(n);
    for (auto &i : scores)
        cin >> i.second >> i.first;
    sort(scores.begin(), scores.end(), [](const auto &x, const auto &y)
         { return x.first == y.first ? x.second < y.second : x.first > y.first; });

    int line = scores[1.5 * m - 1].first,
        num = n - (upper_bound(scores.crbegin(), scores.crend(), make_pair(line, 0)) - scores.crbegin());
    cout << line << ' ' << num << '\n';
    for (auto it = scores.cbegin(); it < scores.cend(); it++)
        if (it->first >= line)
            cout << it->second << ' ' << it->first << '\n';
    return 0;
}