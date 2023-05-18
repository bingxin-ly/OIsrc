#include <bits/stdc++.h>
using namespace std;

int csp[1010][1010];
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1, x; j <= m; j++)
            cin >> x, csp[x][j] = 1;

    for (int i = 1; i <= k; i++)
    {
        int cnt = 0;
        for (int j = 1; j <= m; j++)
            cnt += csp[i][j];
        cout << cnt << ' ';
    }
    return 0;
}