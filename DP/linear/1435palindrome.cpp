#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;
int n, f[N][N];
char s[N];
namespace interval
{
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        cin >> (s + 1), n = strlen(s + 1);
        for (int l = 2; l <= n; l++)
            for (int i = 1; i <= n - l + 1; i++)
            {
                int j = i + l - 1;
                if (s[i] == s[j])
                    f[i][j] = f[i + 1][j - 1];
                else
                    f[i][j] = min(f[i + 1][j], f[i][j - 1]) + 1;
            }
        cout << f[1][n];
        return 0;
    }
}
namespace LCS
{
    char r[N];
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        cin >> (s + 1), n = strlen(s + 1);
        strcpy(r + 1, s + 1), reverse(r + 1, r + n + 1);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (s[i] == r[j])
                    f[i][j] = f[i - 1][j - 1] + 1;
                else
                    f[i][j] = max(f[i - 1][j], f[i][j - 1]);
        cout << n - f[n][n];
        return 0;
    }
}
signed main() { return LCS::main(); }