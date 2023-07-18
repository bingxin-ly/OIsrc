# UVA323 01背包进阶题目

## 简化题意

给定 $n$ 个数对 $(p_i,d_i)$，在其中取出 $m$ 对，使这 $m$ 对中 $|\sum p_i - \sum d_i|$ 最小；当有多个值时，取总和之和更大的。

数据范围：$1 \le N \le 200,1 \le M \le 20,0 \le p_i,d_i \le 20$

## 做法分析

既然题目中已经给出了我们这 $m$ 个数对，并且每个数对可以选择选或不选这两种情况，那我们就来考虑用 01 背包来做。我们回想，在普通的 01 背包问题中，每个物品所带来的影响只有 **体积** 和 **价值** 这两个维度，其中价值是我们要求的，而体积用来做转移的状态。然而这道题可以看到，每对数不仅占了一份体积，还都附带了 $(p_i,d_i)$ 的附加信息，这就需要我们将 01 背包问题搬到 **高维** 上来做。

搬到高维上的 01 背包我们如法炮制，我们首先尝试出一种可行方案，然后在可行方案中求出我们想要的最优方案。设 $f_{i,j,d,p}$ 表示：

1. 考虑到第 $i$ 个人 ($1 \le i \le n$)
2. 当前选了 $j$ 个人 ($1 \le j \le i$)
3. 候选人 $d$ 值之和 ($0 \le d \le 20 \times j$)
4. 候选人 $p$ 值之和 ($0 \le p \le 20 \times j$)

这样，我们把人看做物品，考虑每个物品取不取，当外层循环到 $i$ 时，表示已经考虑了前 $i$ 个人，我们用背包 **滚动数组** 优化掉一维，有转移方程:
$$f_{j,d,p} = f_{j,d,p} \ \operatorname{or} \ f_{j - 1,d - D_i,p - P_i}$$
那么我们最后循环一下，求出所有为 true 的状态中 $|d - p|$ 尽量小，有多个值时 $d + p$ 尽量大的状态。

这样对不对呢？可以看到，我们 **分阶段、有顺序、无重复** 地遍历到了每一种情况，但我们考虑这个解法的复杂度却有点不尽人意：每个维度的循环范围已在上文给出，这样解法总体的复杂度便是 $O(NM^5)$ 的（$20$ 与 $M$ 直接同阶了都），而且这样写还有一个坏处：**决策性不够明显**，我们这样设计考虑的是方案的可行性，转移时是或出来的（冷门操作），导致我们并不好解决输出方案这一问。

当然，为了方便大家理解上面的前置状态设计，我也写了一份这样的代码，其中求出来了 $d$ 值和 $p$ 值。~~如果有大佬能好心填一下这个状态记录的话非常感谢orz。~~

```cpp
constexpr int N = 205, M = 25;
int n, m, P[N], D[N];
bool f[M][20 * M][20 * M];
void solve()
{
    for (int i = 1; i <= n; i++)
        cin >> P[i] >> D[i];
    f[0][0][0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = i; j; j--)
            for (int d = 0; d <= 20 * j; d++)
                for (int p = 0; p <= 20 * j; p++)
                    f[j][d][p] |= f[j - 1][d - D[i]][p - P[i]];
    int ansd = 0x3f3f3f3f, ansp = ~0x3f3f3f3f;
    for (int d = 0; d <= 20 * m; d++)
        for (int p = 0; p <= 20 * m; p++)
            if (f[m][d][p])
            {
                if (abs(ansd - ansp) > abs(d - p))
                    ansd = d, ansp = p;
                else if (abs(ansd - ansp) == abs(d - p) && d + p > ansd + ansp)
                    ansd = d, ansp = p;
            }
    cout << ansd << ' ' << ansp;
}
```

我们来考虑这个算法的缺陷：它把所有要维护的信息都堆在了体积上，价值根本就没怎么用，这是不好的。回想我们一开头提到的，价值是我们要求解的并作为 DP 数组的值，我们也试试把其中的体积转化一下，搞一搞转化一个价值出来。

他要的第一关键字是相差最小，能不能存这些人 $d,p$ 之差的绝对值呢？不太行，因为这个最优解并不能导出后面的最优解。加入后边来的这个人一边倒，加上他之后差值就非常大了，根本没法搞。看来差值还是得当成状态，我们换一下，把第二关键字作为值，并在代码里取一下最大值就 ok 了，每新增一个人，导出他之前的差值也非常容易。

设当外层循环到 $i$ 时，设 $f_{j,k}$ 表示在前 $i$ 个人中选出了 $j$ 个，此时 $d - p$ 的差（注意这里是绝对差）为 $k$ 时，双方总和的最大值。有转移：
$$f_{j,k} = \max\limits_{0 \le j \le \min \{i,m\},-20 \times j \le k \le 20 \times j} \{f_{j - 1,k - (D_{i} - P_{i})} + D_{i} + P_{i}\}$$
可能你会注意到，我们在循坏枚举绝对差值的时候，有一半情况数组下标都用的是负数，C++里不允许出现负下标，我们就简单粗暴的给每一个用到 $f$ 数组和 $c$ 数组的地方第二维加一个偏移量，然后就没问题了。

最后我们浅找一下 $f_{m,k}$ 中满足 $|k|$ 最小，相同时 $f_{m,k}$ 最大即可。其中我们使用了滚动数组，转移时保证 $j$ 这一维 **倒序循环** 即可，确保不会被重复选。

最后，本体还要求输出具体方案，由于 01 背包的决策就是选或不选，所以我们记录一个三维 bool 数组 $c_{i,j,k}$ 表示考虑第 $i$ 个人时，$f_{j,k}$ 选了这人没有，套路地把 $\max$ 函数换一下就行，求完之后沿着数组 $c$ 回溯一下 $(i,j,k) \rightarrow (i - 1,j - 1,k - (D_{i} - P_{i}))$。

*以上的每一句话都可在代码中找到详细体现，小的注意事项也写在了注释里。*

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205, M = 25, offset = 400;
int n, m, T, p[N], d[N], f[M][2 * 20 * M];
bool c[N][M][2 * 20 * M]; // 我们要记录的是所有的决策路径, 带上N捏

void print(int i, int j, int k)
{
    if (!j)
        return;
    if (c[i][j][k + offset])
        print(i - 1, j - 1, k - (d[i] - p[i])),
            cout << ' ' << i; // 注意 UVA 地狱输出格式
    else
        print(i - 1, j, k);
}
void solve()
{
    for (int i = 1; i <= n; i++)
        cin >> p[i] >> d[i];
    memset(f, ~0x3f, sizeof(f)); // 求最大值, 我们设初值为负无穷
    f[0][0 + offset] = 0; // 不选人总和为 0
    for (int i = 1; i <= n; i++)
        for (int j = min(i, m); j; j--) // 范围应该很好理解
            for (int k = -20 * j; k <= 20 * j; k++)
            {
                c[i][j][k + offset] = false; // 不选的情况很多, 但选的很少, 所以先默认不选
                if (k - (d[i] - p[i]) < -20 * j || k - (d[i] - p[i]) > 20 * j)
                    continue; // 越界 & 非法情况拜拜
                if (f[j][k + offset] < f[j - 1][k - (d[i] - p[i]) + offset] + d[i] + p[i])
                {
                    f[j][k + offset] = f[j - 1][k - (d[i] - p[i]) + offset] + d[i] + p[i];
                    c[i][j][k + offset] = true; // 只在这里更新一次就好了
                }
            }
    int dlt = 1 << 30, sum = 0, dif = 0;
    for (int k = -20 * m; k <= 20 * m; k++)
    {
        if (f[m][k + offset] < 0)
            continue;
        if (abs(k) < dlt)
            dlt = abs(k), sum = f[m][k + offset], dif = k;
        else if (abs(k) == dlt && f[m][k + offset] > sum)
            sum = f[m][k + offset], dif = k;
    }
    cout << "Jury #" << ++T << '\n' // UVA地狱输出格式提醒
         << "Best jury has value " << ((sum - dif) >> 1) << " for prosecution and value " << ((sum + dif) >> 1) << " for defence:\n";
    print(n, m, dif); // 回溯方案
    cout << "\n\n";
    /* Jury #1
       Best jury has value 6 for prosecution and value 4 for defence:
        2 3 */
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m)
        solve();
    return 0;
}
```
