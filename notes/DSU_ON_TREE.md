## DSU_ON_TREE（树上启发式算法）

> 启发式算法大家最熟悉的一定是并查集的按秩合并了，合并的代码是这样的：
>
> ```cpp
> void merge(int x, int y)
> {
>    x = find(x), y = find(y);
>    if (size[x] < size[y])
>        swap(x, y);
>    fa[y] = x;
>    size[x] += size[y];
> }
> ```
>
> 在这里，对于两个大小不一样的集合，我们将小的集合合并到大的集合中，以降低复杂度。

但是像这样简单粗暴地去运用定义的题实在是太少了，导致如果你只知道这个解释的话可能一道题都切不出来，如果我们追寻七年前 **Sack 技巧（technique）** 提出者 Arpa 的足迹的话，我们可以这样理解：

#### 引例

> 给出一棵 $n$ 个节点以 $1$ 为根的树，节点 $u$ 的颜色为 $c_u$，现在对于每个结点 $u$ 询问 $u$ 子树里颜色 c 一共出现了多少次。
> $n\le 2\times 10^5$。

我们可以发现这个问题的几个特征：`树上` `没有修改` `离线`

能想到用什么方法来做？？

能想到用什么方法来做？？

能想到用什么方法来做？？

能想到用什么方法来做？？

能想到用什么方法来做？？

能想到用什么方法来做？？

    A： 离线是什么？我数据结构什么都不知道
    恭喜！这类题大部分都可以用大量的数据结构（线段树合并/树套树等）
    维护并AC，但是对于离线的问题，有没有更简单而不用繁琐地去调代码的方法？

    B：莫队！树上莫队！就在同机房，dalao wjy还讲过，为什么不用？
    不行，莫队带根号，我要 log
    B：加回滚！

如果再简单一点呢？
既然支持离线，考虑预处理后 $O(1)$ 输出答案。

#### 前置

1. 暴力
2. 没了

```cpp
int cnt[maxn];
void add(int v, int p, int x)
{
    cnt[col[v]] += x;
    for(auto u : g[v])
        if(u != p)
            add(u, v, x)
}
void dfs(int v, int p)
{
    add(v, p, 1);
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    add(v, p, -1);
    for(auto u : g[v])
        if(u != p)
            dfs(u, v);
}
```

直接暴力 dfs 处理的时间复杂度为 $O(n^2)$，即对每一个子节点进行一次遍历。可以发现，每个节点的答案由其子树和其本身得到，然而这些信息都被我们浪费了。

我们可以先预处理出每个节点子树的大小和它的 **？？？** （思考：结合启发式合并思想）

<br/><br/><br/>

重儿子：重儿子同树链剖分一样，是拥有节点最多子树的儿子，这个过程显然可以 $O(n)$ 完成

我们用 $cnt[i]$ 表示颜色 $i$ 的出现次数，$ans[u]$ 表示结点 $u$ 的答案。

遍历一个节点 $u$，我们按以下的步骤进行遍历：

先遍历 $u$ 的轻（非重）儿子，并计算答案，但 **不保留** 遍历后它对 $cnt$ 数组的影响；
遍历它的重儿子，保留它对 $cnt$ 数组的影响；
再次遍历 $u$ 的轻儿子的子树结点，加入这些结点的贡献，以得到 $u$ 的答案。

~~DSU_ON_TREE 有四种写法，我告诉你，记着，将来······~~
第一种方法用 map 实现，多个 log，不再赘述
第二种：

```cpp
// implemented by STL vector
vector<int> *vec[maxn];
int cnt[maxn];
void dfs(int v, int p, bool keep)
{
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
           mx = sz[u], bigChild = u;
    for(auto u : g[v])
       if(u != p && u != bigChild)
           dfs(u, v, 0);
    if(bigChild != -1)
        dfs(bigChild, v, 1), vec[v] = vec[bigChild];
    else
        vec[v] = new vector<int> ();
    vec[v]->push_back(v);
    cnt[col[v]]++;
    for(auto u : g[v])
       if(u != p && u != bigChild)
           for(auto x : *vec[u]){
               cnt[col[x]]++;
               vec[v]->push_back(x);
           }
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c.
    // note
    if(!keep)
        for(auto u : *vec[v])
            cnt[col[u]]--;
}
```

很明显，在注释的位置`vec[v]`包含了子树的所有节点，我们对子树的暴力更新就是依靠里面存储的信息实现的
**第三种（重要）：**
重链剖分风格，你们以后写的代码大部分就都是这种风格了/kk

```cpp
int heavy, cnt[maxn];
void add(int v, int p, int x)
{
    cnt[col[v]] += x;
    for(auto u : g[v])
        if(u != p && u != heavy)
            add(u, v, x);
}
void dfs(int v, int p, bool keep)
{
    for(auto u : g[v])
        if(u != p && u != son[v])
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(son[v] != -1)
        dfs(son[v], v, 1), heacy = son[v];  // bigChild marked as big and not cleared from cnt
    add(v, p, 1);
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    heavy = 0;
    if(!keep)
        add(v, p, -1);
}
```

这份代码是纯纯的板子，而对于不同的题目，只需改变 add 函数即维护答案的部分即可
第四种：
_性质：一个节点内子树的 dfn 序是连续的（致谢 wjy）_
在预处理时记录下每个节点的子树起始 dfn 和终止 dfn，更新是 for 过去就行，只是一个常数优化，就说这么多吧。

#### 题

我们已经学了 dsu 的经典使用方法，快来切一下[这道模板题](https://www.luogu.com.cn/problem/U41492)吧
[CF246E 血亲归来（？](https://codeforces.com/problemset/problem/246/E)
[CF570D Tree Requests](https://codeforces.com/problemset/problem/570/D)
加菜：[SGU507 Treediff](https://codeforces.com/problemsets/acmsguru/problem/99999/507)
