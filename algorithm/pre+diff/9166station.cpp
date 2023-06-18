#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 10;
int diff[N], cans[N], rails[N];
int main()
{
    int n, m, x;
    cin >> n >> m >> x;
    n *= 2, x *= 2;
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> u >> v;
        u *= 2, v *= 2;
        diff[u]++, diff[v + 1]--;
        if (v > x)
            cans[v] = true;
        if (u < x)
            cans[u] = true;
    }
    for (int i = 1; i <= n; i++)
        rails[i] = rails[i - 1] + diff[i];
    vector<int> tmp;
    for (int i = x; i >= 1; i--)
        if (!rails[i])
            break;
        else if (cans[i])
            tmp.push_back(i);
    for (auto i = tmp.rbegin(); i < tmp.rend(); i++)
        cout << *i / 2 << ' ';
    for (int i = x + 1; i <= n; i++)
        if (!rails[i])
            break;
        else if (cans[i])
            cout << i / 2 << ' ';
    return 0;
}
