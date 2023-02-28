#include <bits/stdc++.h>
#define MX 1000
using namespace std;
int n, tagl[MX][MX];
int vis[MX][MX]; // 递归或者作为递推数组，就像union
int (*k)[MX] = vis;// vis的引用，内容实际上相同

int f(int i, int j)
{
    if (vis[i][j] != -1)
        return vis[i][j];
    if (i == n - 1)
        return tagl[i][j];
    else
    {
        int ans = max(f(i + 1, j), f(i + 1, j + 1)) + tagl[i][j];
        vis[i][j] = ans;
        return ans;
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
        {
            cin >> tagl[i][j];
            vis[i][j] = -1;
        }
    // 递归
    cout << f(0, 0) << endl;
    // 递推
    for (int i = n - 1, j = 0; j < n; j++)
        k[i][j] = tagl[i][j];
    for (int i = n - 2; i > -1; i--)
        for (int j = 0; j <= i; j++)
            k[i][j] = max(k[i + 1][j], k[i + 1][j + 1]) + tagl[i][j];
    cout << k[0][0] << endl;
    return 0;
}