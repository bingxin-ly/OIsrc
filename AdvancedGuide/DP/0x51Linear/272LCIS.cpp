/* LCS问题需要知道当前考虑到了A、B串的哪个位置，LIS问题需要知道当前串的结尾是多少。
   而在实际做的时候，你一定不想B串同时考虑求解的位置与结尾这两个状态，所以我们可以在LIS的基本上扩展，
   在已上升的子序列中，考虑公共的部分，涉及状态时将A套到外层即可：
   F[i, j]表示 A1~Ai与 B1~Bj 可以构成的以 Bj结尾的 LCIS 的长度（B序列LIS，同时与A序列LCS）
   转移时，有：当 Ai != Bj 时，F[i, j] = F[i - 1, j]
              当 Ai == Bj 时，F[i, j] = max(0<=k<j,Bk<Bj){F[i - 1, k]} + 1
   很显然看一看使用三重循环解决。
   但在转移过程中，我们关注决策集合，（我们把满足 0<=k<j,Bk<Bj 的 k 构成的集合称为 F[i, j] 进行状态转移时的决策集合，
   记为 S(i, j)。注意到，j 从 1 变为 m 的过程中，整数 j 可能进入决策集合仅当 Bj < Ai，而已经在决策集合中的数一定不会删除，
   对于“决策集合中的元素只增多不减少”的情景，我们用一个数据结构来维护这个最大值，即可避免重复扫描，把转移的复杂度降低一个量级。
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 3005;
int a[N], b[N];
int f[N][N]; // 表示 A1 ~ Ai 与 B1 ~ Bj 可以构成的以 Bj 为结尾的 LCIS 的长度
signed force()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i] != b[j])
                f[i][j] = f[i - 1][j];
            else
                for (int k = 0; k < j; k++)
                    if (b[k] < a[i])
                        f[i][j] = max(f[i][j], f[i - 1][k] + 1);
    int ans = 0;
    for (int j = 1; j <= n; j++)
        ans = max(ans, f[n][j]);
    cout << ans;
    return 0;
}
int n, m, pos[N][N];
void print(int p)
{
    if (!p)
        return;
    print(pos[n][p]);
    cout << b[p] << ' ';
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    // cin >> m;
    m = n;
    for (int i = 1; i <= m; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
    {
        int p = 0;
        for (int j = 1; j <= m; j++)
        {
            if (a[i] != b[j])
                f[i][j] = f[i - 1][j], pos[i][j] = pos[i - 1][j];
            else
                f[i][j] = f[i - 1][p] + 1, pos[i][j] = p;
            if (b[j] < a[i] && f[i - 1][j] > f[i - 1][p])
                p = j;
        }
    }
    int p = 0;
    for (int j = 1; j <= m; j++)
        if (f[n][j] > f[n][p])
            p = j;
    cout << f[n][p] << '\n';
    // print(p);
    return 0;
}