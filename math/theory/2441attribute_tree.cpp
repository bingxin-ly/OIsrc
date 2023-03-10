// C++ 17
#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 10;
int memb[MAX], fa[MAX];
int dfs(int x, int y)
{
    if (x == 0)
        return -1;
    if (gcd(memb[x], memb[y]) > 1)
        return x;
    return dfs(fa[x], y);
}
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> memb[i];
    for (int i = 1; i <= n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        fa[y] = x;
    }
    for (int i = 1; i <= k; i++)
    {
        int x, y;
        cin >> x;
        if (x == 1)
        {
            cin >> y;
            cout << dfs(fa[y], y) << endl;
        }
        else
        {
            cin >> x >> y;
            memb[x] = y;
        }
    }
    return 0;
}
