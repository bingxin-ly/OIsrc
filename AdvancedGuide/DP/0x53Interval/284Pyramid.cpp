/* 年轻人的第一道图论计数 ~
   首先第一步，我们先把题目从树上搬到序列上来做，输入已经给了这棵树的欧拉序，我们就可以在这个序列上进行 DP。
   接下来考虑区间的划分，和之前的入门题不同，由于有了计数的加持，k 的划分就不能是其中的任意一个数了，
   既要满足原图的树性质，又要有优良的复杂度，以及计数过程中必然要不重不漏；所以枚举分割点和分一半递归子树求都毙掉了。
   我们就应该考虑计数问题的原则：必须找到一个基准，比如 “1”，构建一个完整的基准。
   我们在枚举分割点时，就只考虑字串 s[l~r] 的 **第一棵子树** 是怎样构成的，剩下的作为其他的部分。
   这样前半段序列只会作为一棵树，如果 k 不相同，那么这棵树大小不相同，就不可能产生重复计数。
   总结：对于方案计数，通常一个状态的各个决策之间满足 “加法原理”，而每个决策划分的几个子状态之间满足 “乘法原理”。
   在设计状态转移方程的决策方式与划分方法时，一个状态的所有决策之间必须具有互斥性，才能保证不会出现重复问题。
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 305, MOD = 1e9;
char s[N];
int n, f[N][N];

int dp(int l, int r)
{
    if (l > r || s[l] != s[r])
        return 0;
    if (l == r)
        return 1;
    if (f[l][r] != -1)
        return f[l][r];
    for (int k = l + 2; k <= r; k++)
        if (s[l] == s[k])
            (f[l][r] += 1ll * dp(l + 1, k - 1) * dp(k, r) % MOD) %= MOD;
    return f[l][r];
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> (s + 1), n = strlen(s + 1);
    cout << (memset(f, -1, sizeof(f)), dp(1, n));
    return 0;
    for (int i = 1; i <= n; i++)
        f[i][i] = 1;
    for (int len = 2; len <= n; len++)
        for (int l = 1; l <= n - len + 1; l++)
        {
            int r = l + len - 1;
            if (s[l] != s[r])
                continue;
            f[l][r] = f[l + 1][r - 1];
            for (int k = l + 2; k <= r - 2; k++)
                if (s[l] == s[k])
                    (f[l][r] += 1ll * f[l + 1][k - 1] * f[k][r] % MOD) %= MOD;
        }
    cout << f[1][n];
    return 0;
}