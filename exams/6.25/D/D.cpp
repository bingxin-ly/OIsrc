#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N = 1e5 + 5;
int n, q;
pair<int, int> ls[N], qu[N];
vector<int> v;

void dfs(int x)
{
    if (v.size() > 2 || v.size() + (n - x + 1) < 2)
        return;
#define k first
#define b second
    if (x == n + 1)
    {
        int i = v[0], j = v[1];
        for (int l = 1; l <= q; l++)
        {
            int r1 = ls[j].k * (ls[i].k * qu[l].first + ls[i].b) + ls[j].b;
            swap(i, j);
            int r2 = ls[j].k * (ls[i].k * qu[l].first + ls[i].b) + ls[j].b;
            qu[l].second = max(qu[l].second, r1), qu[l].second = max(qu[l].second, r2);
        }
        return;
    }
    v.emplace_back(x), dfs(x + 1), v.pop_back();
    dfs(x + 1);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> ls[i].k >> ls[i].b;
#undef k
#undef b
    cin >> q;
    for (int i = 1; i <= q; i++)
        cin >> qu[i].first;
    dfs(1);
    for (int i = 1; i <= q; i++)
        cout << qu[i].second << '\n';
    return 0;
}