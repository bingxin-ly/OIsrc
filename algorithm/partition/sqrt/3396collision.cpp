#include <bits/stdc++.h>
using namespace std;

const int N = 1.5e5 + 10;
int n, up, arr[N], ans[400][400];

int query(int p, int x)
{
    if (p <= up)
        return ans[p][x];
    int res = 0;
    for (int i = x; i <= n; i += p)
        res += arr[i];
    return res;
}
void change(int x, int y)
{
    for (int p = 1; p <= up; p++)
        ans[p][x % p] = ans[p][x % p] - arr[x] + y;
    arr[x] = y;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int m;
    cin >> n >> m, up = sqrt(n);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    for (int p = 1; p <= up; p++)
        for (int i = 1; i <= n; i++)
            ans[p][i % p] += arr[i];

    char cmd;
    for (int x, y; m--;)
    {
        cin >> cmd >> x >> y;
        if (cmd == 'A')
            cout << query(x, y) << '\n';
        else
            change(x, y);
    }
    return 0;
}