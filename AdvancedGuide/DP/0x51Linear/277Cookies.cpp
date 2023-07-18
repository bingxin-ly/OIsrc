/* 优雅！和之前动辄 5、6 维的 DP 不同，以后见到的线性 DP 大部分都是长这样的
   首先这道题在设计状态的时候就并不直接：如果仅设 i 个孩子 j 块饼干，会根本无法转移
   不仅没有最优子结构，无后效性也保证不了。无脑 DP 遇到瓶颈，考虑找性质，比如贪心：
   看这个怨气是怎么算出来的：每个孩子的怨气值 = 他的怨气系数 * 拿到饼干比他多的人
   因为我们要求怨气总和最小，我们就贪心地试试直接给怨气系数大的孩子多分饼干，让最后乘起来小一些
   这个贪心可以用邻项交换法简单地证明，但是因为我太菜了，只会口胡。
   所以我们先排个序，通过这一步就能保证分配的饼干数是不上升的，每个孩子的怨气值都只从他前面转移过来
   但是再解决第二个问题的时候，我们会发现还是不太好转移，第 i + 1 个孩子的饼干 <= 第 i 个孩子的饼干，
   但具体是多少呢？多一个 3k 的枚举好像让人不太乐意。这里就用到一个等价转化了，转化为与个数无关的问题
   我们想想：这个孩子的怨气值和他具体分到的饼干数并没有什么关系，他们之前只需保证一个相对大小
   当给这个孩子分的饼干数大于 1 时，答案就等于每个孩子都少给一块饼干的答案，因为相对大小是不变的
   而当饼干数等于 1 时，我们枚举可能前面有多少个孩子和他拿的一样（也是 1），然后再转移就可以了
   （虽然说完理解难度不是很大，但要自己想出来还是要一些功底的，一定要画画图）
   这样，在大于 1 时转化为等效的问题，等于 1 时才实际去计算，完全抛开了具体个数给我们的桎梏。

   做这些没有用的，多看点贪心 DP。 ——小粉兔
 */
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 35, M = 5005;
int n, m, g[N], c[N], s[N], ans[N];
int f[N][M], a[N][M], b[N][M];

void back(int n, int m)
{
    if (!n)
        return;
    back(a[n][m], b[n][m]);
    if (a[n][m] == n)
        for (int i = 1; i <= n; i++)
            ans[c[i]] += 1; // 加回来
    else
        for (int i = a[n][m] + 1; i <= n; i++)
            ans[c[i]] = 1; // 这一段都是 1
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> g[i], c[i] = i; // 我们记录一个编号，方便回溯
    sort(c + 1, c + n + 1, [](int a, int b)
         { return g[a] > g[b]; }); // 我们贪心地给贪婪值更大的多分

    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        s[i] = s[i - 1] + g[c[i]];
        for (int j = i; j <= m; j++)
        {
            f[i][j] = f[i][j - i];
            a[i][j] = i, b[i][j] = j - i;
            for (int k = 0; k < i; k++)
            {
                if (f[i][j] > f[k][j - (i - k)] + k * (s[i] - s[k]))
                {
                    f[i][j] = f[k][j - (i - k)] + k * (s[i] - s[k]);
                    a[i][j] = k, b[i][j] = j - (i - k);
                }
            }
        }
    }
    cout << f[n][m] << endl;
    back(n, m);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    return 0;
}