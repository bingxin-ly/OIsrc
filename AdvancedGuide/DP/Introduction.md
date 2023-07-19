# 动态规划总论

对于一个问题的状态空间的遍历，总是要基于一些信息，或是指明当前解决到了哪个问题，或是提供得出当前问题的解的附加信息。而这种对于状态空间朴素的遍历，常见的方法便是使用 dfs 搜索，它遍历整个状态空间以得出所有的解。实现时通常依靠：

- 参数：指明当前解决的问题阶段
- 局部变量：当前当前状态空间中的统计
- 全局变量：有时也有局部性，即一些不便传递的参数，或保存了全局的最优解  

但通常我们需要在这些信息的基础上稍加思考：在推导时哪些是不必要的，哪些是可以通过其他信息导出的，这样，我们可以舍掉许多不必要的，难以存储的信息，把它们最终变为几个数字（或只有在万不得已时存很小的状态，通常不过20~30），而简化问题的推导。

这种方式虽然遍历了所有的状态空间，但有时候所有的状态可能很多，遍历所有未免规模很大，无法在可观的时间内求解，但如果分析新问题的求解得到我们并不都需要平地起高楼，而是可以通过之前的解推导得出，那么就可以在之前的解上 **转移** ，来得出解，如果我们知道了这个转移到的过程，那么我们在dfs的框架上稍加记忆化即可得到，加快了求解的速度。

最后如果我们把第一步的 **简化状态** 与 **阶段转移** 结合起来，便很可能能抛开 dfs 函数的限制，将各个阶段与状态作为数组的下标，使用 for 循环来更新状态，这样我们就从空间与时间两方面优化，将 dfs 搜索整合为了一个 DP动态规划问题，而前面提到的几个步骤，术语概括来讲便是“**最优子结构性质**”与“**状态转移方程**”，而这将搜索变为动归的两步往往是最困难的，不仅需要教程来领进大门，更需要自己在联系中不断地体悟。

附注：求方案时记录每一步的决策，使用递归函数打印

下面为原文：
/*
问题（形式化）
方案的初始形态
   ↓
中间形态
   ↓
中间形态
   ↓
目标（可行方案 / 最优方案）
状态空间

搜索：初态 边界 所有可能搜到的状态

1. 定义状态（存什么，哪些全局变量+哪些是参数+局部变量）
2. 简化状态（用最少的值去代表一个状态）
3. 推导（怎么从一个状态搜到下一个状态）

*/

```plain
A = {3, 1, 2, 8, 2, 5, 9}, N = 7
B = {3,    2, 8}
k = {1,    3, 4}

B = {   1, 2, 8,       9}
k = {   2, 3, 4,       7}

B = {   1, 2} = {  A[2], A[3]}
k = {   2, 3}

   B = {  1, 2, 8}
=> k = {  2, 3, 4}
```

下标序列就是中间状态
状态空间：所有可能的下标序列

```cpp
int n, a[105];
int k[105], ans;
void dfs(int len) {
   if (len > ans) {
      ans = len;
      // 如果需要方案，记录 {A[k[1]], A[k[2]], ..., A[k[len]]}
   }
   // {k[1], k[2], ..., k[len]}
   // B = {A[k[1]], A[k[2]], ..., A[k[len]]}
   for (int i = k[len] + 1; i <= n; i++)
      if (a[i] > a[k[len]]) {
         k[len + 1] = i;
         dfs(len + 1);
      }
}
k[0] = 0, a[0] = -(1<<30);
dfs(0);
```

虽然维护了一个长度为len的序列（len个数）
但是其实我们推导时只用到了k[len]这个结尾

```cpp
void dfs(int len, int tail) {
   if (len > ans) {
      ans = len;
   }
   for (int i = tail + 1; i <= n; i++)
      if (a[i] > a[tail])
         dfs(len + 1, i);
}
a[0] = -(1<<30);
dfs(0, 0);
```

| 子结构（以8为结尾的上升子序列） | 代表元素 | 最优解           |
| ------------------------------- | -------- | ---------------- |
| {1, 2, 8}                       | 8        | {1, 2, 8}, len=3 |
| {3, 8}                          |          |                  |
| {1, 8}                          |          |                  |
| {2, 8}                          |          |                  |
| {8}                             |          |                  |

更大的子结构
（以9为结尾的上升子序列）

当子结构之间都可以用代表元素和最优解来推导时
称问题满足最优子结构性质

新状态：结尾下标
状态总数：n
f[i]表示以a[i]为结尾的最长上升子序列的长度

```cpp
// 第一种写法：考虑f[i]可以推导到哪些状态
f[0] = 0;
for (int i = 0; i < n; i++) // i: 结尾下标
   for (int j = i + 1; j <= n; j++) // 下一个数
      if (a[j] > a[i]) f[j] = max(f[j], f[i] + 1);

// 第二种写法：考虑f[i]可以由哪些状态得到
f[0] = 0;
for (int i = 1; i <= n; i++)
   if (int j = 0; j < i; j++) // 前一个数
      if (a[j] < a[i]) f[i] = max(f[i], f[j] + 1);

// 求方案
f[0] = 0;
for (int i = 1; i <= n; i++)
   if (int j = 0; j < i; j++) // 前一个数
      if (a[j] < a[i])
         if (f[j] + 1 > f[i]) {
            f[i] = f[j] + 1;
            pos[i] = j;
         }

int ans = 0, tail;
for (int i = 1; i <= n; i++)
   if (f[i] > ans) ans = f[i], tail = i;

void print(int i) {
   if (i == 0) return;
   print(pos[i]);
   cout << a[i] << " ";
}

print(tail);
```

> 作者：lydrainbowcat
> 链接：<https://www.acwing.com/activity/content/code/content/590726/>
> 来源：AcWing
> 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。