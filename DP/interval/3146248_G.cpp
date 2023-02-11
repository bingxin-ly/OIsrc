// 此题无需判环！！
#include <bits/stdc++.h>
using namespace std;

const int MAX = 250;
int n, ans, f[MAX][MAX];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> f[i][i];
    for (int len = 1; len < n; len++)
        for (int i = 1, j = i + len; j <= n; i++, j++)
            for (int k = i; k < j; k++)
                if (f[i][k] == f[k + 1][j])
                    f[i][j] = max(f[i][j], f[i][k] + 1),
                    ans = max(ans, f[i][k] + 1);
    // cout << f[1][n] << endl;
    // 最终答案不一定是f[1][n]，因为整个区间并不一定都能够合并在一起
    cout << ans << endl;
    return 0;
}