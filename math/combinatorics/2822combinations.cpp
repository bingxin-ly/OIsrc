#include <bits/stdc++.h>
using namespace std;

const int N = 1e4;
size_t k, c[N][N], ans[N][N];
inline void build()
{
    c[0][0] = 1;
    c[1][0] = c[1][1] = 1;
    for (int i = 2; i <= 2000; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % k;
            ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1];
            if (!c[i][j])
                ans[i][j]++;
        }
        ans[i][i + 1] = ans[i][i];
    }
}
int main()
{
    int t;
    cin >> t >> k;
    build();
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        cout << ans[n][m > n ? n : m] << endl;
    }
    return 0;
}
