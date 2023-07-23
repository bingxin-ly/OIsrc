#include <bits/stdc++.h>
using namespace std;

int n, m, tab[30][30], tmp[30][30];
pair<int, int> sav[1005];

int floyd()
{
    memcpy(tmp, tab, sizeof(tab));
    for (int k = 1; k <= n; k++)
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
                tmp[u][v] |= tmp[u][k] & tmp[k][v];
    bool ncr = false;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            if (tmp[u][v] & tmp[v][u])
                return -1;
            else if ((!tmp[u][v] & !tmp[v][u]) && (u != v))
                ncr = true;
    return !ncr;
}
void solve()
{
    char rel[5];
    for (int i = 1; i <= m; i++)
        cin >> rel,
            sav[i].first = rel[0] - 'A' + 1, sav[i].second = rel[2] - 'A' + 1;
    for (int i = 1; i <= m; i++)
    {
        tab[sav[i].first][sav[i].second] = 1;
        switch (floyd())
        {
        case -1:
            return cout << "Inconsistency found after " << i << " relations.\n", void();
        case 0:
            break;
        case 1:
            cout << "Sorted sequence determined after " << i << " relations: ";
            int seq[30];
            iota(seq + 1, seq + n + 1, 1);
            sort(seq + 1, seq + n + 1, [](int x, int y)
                 { return tmp[x][y]; });
            for (int i = 1; i <= n; i++)
                cout << char(seq[i] + 'A' - 1);
            return cout << ".\n", void();
        }
    }
    cout << "Sorted sequence cannot be determined.\n";
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m)
        solve(), memset(tab, 0, sizeof(tab));
    return 0;
}