#include <bits/stdc++.h>
#define chkmax(_a, _b) _b > _a ? _a = _b : _a
#define chkmin(_a, _b) _b < _a ? _a = _b : _a
#define u first
#define v second
using namespace std;

typedef pair<int, int> line;
bool specmp(const line &a, const line &b)
{
    return a.second > b.second ||
           (!(b.second > a.second) && a.first > b.first);
}
bool cans[200010];

int main()
{
    ios::sync_with_stdio(false);
    int n, m, x;
    cin >> n >> m >> x;
    vector<line> uprotes, downrotes;
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        if (u >= x)
            uprotes.push_back({u, v});
        else if (v <= x)
            downrotes.push_back({u, v});
        else
            uprotes.push_back({x, v}), downrotes.push_back({u, x});
    }

    sort(uprotes.begin(), uprotes.end());
    sort(downrotes.begin(), downrotes.end(), specmp);

    int prev = x, curr;
    for (auto i : uprotes)
    {
        curr = i.u;
        if (curr <= prev)
            cans[i.v] = true, chkmax(prev, i.v);
        else
            break;
    }

    prev = x;
    for (auto i : downrotes)
    {
        curr = i.v;
        if (curr >= prev)
            cans[i.u] = true, chkmin(prev, i.u);
        else
            break;
    }

    for (int i = 1; i <= n; i++)
        if (cans[i])
            cout << i << ' ';
    return 0;
}