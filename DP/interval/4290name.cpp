#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> trs{{'W', 1}, {'I', 2}, {'N', 3}, {'G', 4}};
constexpr int N = 205;
int n, q[5], a[N], can[5][5][5], f[N][N][5];
char s[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    for (int i = 1; i <= 4; i++)
        cin >> q[i];
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= q[i]; j++)
            cin >> s, can[i][trs[s[0]]][trs[s[1]]] = true;
    cin >> (s + 1), n = strlen(s + 1);
    for (int i = 1; i <= n; i++)
        a[i] = trs[s[i]], f[i][i][a[i]] = true;
    for (int l = 2; l <= n; l++)
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            for (int k = i; k < j; k++)
                for (int c = 1; c <= 4; c++)
                    for (int c1 = 1; c1 <= 4; c1++)
                        for (int c2 = 1; c2 <= 4; c2++)
                            if (can[c][c1][c2] && f[i][k][c1] && f[k + 1][j][c2])
                                f[i][j][c] = true;
        }
    bool flag = false;
    if (f[1][n][1])
        cout << 'W', flag = true;
    if (f[1][n][2])
        cout << 'I', flag = true;
    if (f[1][n][3])
        cout << 'N', flag = true;
    if (f[1][n][4])
        cout << 'G', flag = true;
    if (!flag)
        cout << "The name is wrong!";
    return 0;
}