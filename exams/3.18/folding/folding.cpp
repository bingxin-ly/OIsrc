#include <bits/stdc++.h>
#define chkmin(a, b) b < a ? a = b : a
using namespace std;

const int N = 110;
int n, ans, f[N][N];
char str[N];

int cal(int n)
{
    int cnt = 0;
    for (; n; n /= 10)
        cnt++;
    return cnt + 2;
}

bool check(int l, int r, int rr)
{
    for (int i = l, j = l; i <= rr; i++, j++)
    {
        if (j > r)
            j = l;
        if (str[i] != str[j])
            return false;
    }
    return true;
}
int main()
{
    cin >> (str + 1);
    n = strlen(str + 1);

    for (int l = 1; l <= n; l++)
        for (int i = 1, j = i + l - 1; j <= n; i++, j++)
        {
            f[i][j] = l; // 初始化
            for (int k = 1; k < l; k++)
                if (!(l % k) && check(i, i + k - 1, j))
                    chkmin(f[i][j], f[i][i + k - 1] + cal(l / k));
            for (int k = i; k < j; k++)
                chkmin(f[i][j], f[i][k] + f[k + 1][j]);
        }
    cout << f[1][n] << endl;
    return 0;
}
