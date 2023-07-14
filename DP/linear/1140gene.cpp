#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;
map<pair<char, char>, int> fee{
    {{'A', 'A'}, 5},
    {{'A', 'C'}, -1},
    {{'A', 'G'}, -2},
    {{'A', 'T'}, -1},
    {{'A', '-'}, -3},
    {{'C', 'A'}, -1},
    {{'C', 'C'}, 5},
    {{'C', 'G'}, -3},
    {{'C', 'T'}, -2},
    {{'C', '-'}, -4},
    {{'G', 'A'}, -2},
    {{'G', 'C'}, -3},
    {{'G', 'G'}, 5},
    {{'G', 'T'}, -2},
    {{'G', '-'}, -2},
    {{'T', 'A'}, -1},
    {{'T', 'C'}, -2},
    {{'T', 'G'}, -2},
    {{'T', 'T'}, 5},
    {{'T', '-'}, -1},
    {{'-', 'A'}, -3},
    {{'-', 'C'}, -4},
    {{'-', 'G'}, -2},
    {{'-', 'T'}, -1},
    {{'-', '-'}, 0},
};
int n, m, f[N][N];
char a[N], b[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> (a + 1) >> m >> (b + 1);
    memset(f, ~0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        f[i][0] = f[i - 1][0] + fee[{a[i], '-'}];
    for (int j = 1; j <= m; j++)
        f[0][j] = f[0][j - 1] + fee[{'-', b[j]}];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            f[i][j] = max(
                {f[i - 1][j - 1] + fee[{a[i], b[j]}],
                 f[i - 1][j] + fee[{a[i], '-'}],
                 f[i][j - 1] + fee[{'-', b[j]}]});
        }
    cout << f[n][m];
    return 0;
}