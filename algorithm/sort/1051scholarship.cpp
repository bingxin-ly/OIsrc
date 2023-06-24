#include <bits/stdc++.h>
using namespace std;

unordered_map<string, pair<int, int>> tot;
void judge(const string &name, int term, int clas, bool cadre, bool west, int essay, int idx)
{
    tot[name].second = idx;
    if (term > 80 && essay > 0)
        tot[name].first += 8000;
    if (term > 85 && clas > 80)
        tot[name].first += 4000;
    if (term > 90)
        tot[name].first += 2000;
    if (term > 85 && west)
        tot[name].first += 1000;
    if (clas > 80 && cadre)
        tot[name].first += 850;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    string na;
    int term, clas, essay;
    char cadre, west;
    for (int i = 1; i <= n; i++)
        cin >> na >> term >> clas >> cadre >> west >> essay,
            judge(na, term, clas, cadre == 'Y', west == 'Y', essay, n - i);

    int total = 0;
    pair<int, int> top{0, 0};
    for (const auto &[k, v] : tot)
    {
        total += v.first;
        if (v > top)
            top = v, na = k;
    }
    cout << na << '\n'
         << top.first << '\n'
         << total;
    return 0;
}