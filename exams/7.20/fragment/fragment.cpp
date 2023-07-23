#include <bits/stdc++.h>
using namespace std;

int n, m;
char cur[14][14], tmp[14][14];
int check(const char tab[14][14])
{
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cnt += tab[i][j] != tab[n - i + 1][m - j + 1];
    return cnt;
}
bool sa()
{
    int pre = check(cur);
    if (!pre)
        return true;
    for (double t = 1e3; t >= 0.1; t *= 0.99)
    {
        bool op = rand() & 1;
        int pos;
        if (n == 1)
            pos = 0;
        else
            pos = rand() % ((op ? n : m) - 1) + 1;
        memcpy(tmp, cur, sizeof(cur));
        if (op)
            swap(tmp[pos], tmp[pos + 1]);
        else
            for (int i = 1; i <= n; i++)
                swap(tmp[i][pos], tmp[i][pos + 1]);
        int now = check(tmp);
        if (!now)
            return true;
        else if (exp((now - pre) / t) > 1.0 * rand() / RAND_MAX)
            memcpy(cur, tmp, sizeof(tmp));
        else
            pre = now;
    }
    return false;
}
void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> cur[i][j];
    for (int i = 1; i <= 800; i++)
        if (sa())
            return cout << "YES\n", void();
    cout << "NO\n";
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    srand(time(0));
    int T;
    cin >> T >> T;
    while (T--)
        solve();
    return 0;
}