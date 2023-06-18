这 9 个经典题目，涉及了数列分块的大部分重要思想：

- 区间加，单点查询：基础模板。
- 区间加，区间求和：基础模板，最简单的区间信息合并。
- 区间加，区间查询小于给定值 元素数：维护单调性。
- 区间加，区间查询小于给定值 最大元素：维护单调性。
- 区间开方，区间求和：复杂度分析。
- 单点插入，单点查询：复杂度分析，块状数组。
- 区间加，区间乘，单点查询：较复杂的区间信息合并。
- 区间赋值，查询区间等于给定值元素数：复杂度分析。
- 查询区间最小众数：复杂区间信息的预处理，复杂的区间信息合并。

目录

分块思想
数列分块
引入
划分
查询
修改
复杂度分析
代码
练习
均值法复杂度分析
引入
确定最优块大小
莫队的复杂度
平衡结合
引入
例一
例二
预处理之王
引入
例一
例二
写在最后
引用一下 oi-wiki 的话：

分块的基本思想是：通过对原数据的适当划分，并在划分后的每一个块上预处理部分信息，从而较一般的暴力算法取得更优的时间复杂度。

一些有意思的暴论：

分块就是分治！

没有什么错误，考虑分治思想的抽象过程：

分解问题，对应对原数据的划分。
解决问题，对应查询预处理的信息。
合并贡献，对应将得到的信息合并。
分块完全与上述过程相符合，它实际上就是一种分治思想的具体应用。
特别地，对于不在完整块中的元素，需要暴力统计它们的贡献。

“线段树也是分块！” ：

线段树实质上也是通过对数据的划分，并预处理每块数据的信息。
但线段树可以多次划分数据，直至数据规模为 \(1\)，这点与分块只划分一次有所不同。

线段树与分块都是分治思想的具体应用，因此上面这句话有一定道理。
但过于绝对，于是归到暴论里。

“数组也是分块！”

可看做块大小为 1 的分块。
从形式上来说，完全符合分块的定义，但分块后并没有降低复杂度，严格上说并不能叫分块。

“int 型变量也是分块！”

显然，能提出这么深刻道理的万古神犇，实在是太厉害了！
我专程写博客来膜拜它！

数列分块
引入
Loj6280. 数列分块入门 4

给定一长度为 \(n\) 的数列，有 \(n\) 次操作。
操作分为两种：区间加，查询区间和。
\(1\le n\le 5\times 10^4\)。

划分
首先将序列按每 \(T\) 个元素一块进行分块，并记录每块的区间和。
\(T\) 的大小需要根据实际要求选择，下文复杂度分析部分会详细解析。
划分过程的常用模板：

void PrepareBlock() {
  block_size = T; //根据实际要求选择一个合适的大小。
  block_num = n / block_size; 
  for (int i = 1; i <= block_num; ++ i) { //分配块左右边界。
    L[i] = (i - 1) * block_size + 1;
    R[i] = i * block_size;
  }
  if (R[block_num] < n) { //最后的一个较小的块。
    ++ block_num;
    L[block_num] = R[block_num - 1] + 1;
    R[block_num] = n;
  }
  //分配元素所属的块编号。
  for (int i = 1; i <= block_num; ++ i) {
    for (int j = L[i]; j <= R[i]; ++ j) {
      bel[j] = i;
    }
  }
}
查询
设查询区间 \([l,r]\) 的区间和。

若 \(l,r\) 在同一块内，直接暴力求和即可。块长为 \(T\)，单次查询复杂度上界 \(O(T)\)。

否则答案由三部分构成：

以 \(l\) 开头的不完整块的和。
以 \(r\) 结尾的不完整块的和。
中间的完整块的和。
对于 1、2 两部分，可暴力求和，复杂度上界 \(O(T)\)。
对于 3，直接查询预处理的完整块和即可，复杂度上界 \(O(\frac{n}{T})\)（查询所有的完整块）。
单次查询总复杂度上界 \(O(\frac{n}{T}+T)\)。

修改
修改操作的过程与查询操作相同，设修改区间为 \([l,r]\)。

若 \(l,r\) 在同一块内，直接暴力修改，并更新区间和。块长为 \(T\)，单次修改复杂度上界 \(O(T)\)。

否则将修改区间划分成三部分：

以 \(l\) 开头的不完整块。
以 \(r\) 结尾的不完整块。
中间的完整块。
1、2 直接暴力修改序列，3 给完整的块打上区间加的标记。
单次修改复杂度上界 \(O(\frac{n}{T} +T)\)

复杂度分析
总复杂度为 \(O(n\times (\frac{n}{T} + T))\)。
由均值不等式，\(\frac{n}{T} + T\ge 2\sqrt{\frac{n}{T}\times T} = \sqrt{n}\)，当且仅当 \(\frac{n}{T} = T\) 时等号成立，复杂度最低。
此时块大小为 \(\sqrt{n}\)，总复杂度 \(O(n\sqrt{n})\)。

代码
上古时期出土代码，经现代手段修复后勉强能看。

//知识点：分块
/*
By:Luckyblock
*/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cmath>
#include <cstring>
#define LL long long
const int kN = 5e4 + 10;
//=============================================================
int n, m;
int block_size, block_num, L[kN], R[kN], bel[kN];
LL a[kN], sum[kN], tag[kN];
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void Chkmin(LL &fir, LL sec) {
  if (sec < fir) fir = sec;
}
void PrepareBlock() {
  block_size = sqrt(n); //根据实际要求选择一个合适的大小。
  block_num = n / block_size; 
  for (int i = 1; i <= block_num; ++ i) { //分配块左右边界。
    L[i] = (i - 1) * block_size + 1;
    R[i] = i * block_size;
  }
  if (R[block_num] < n) { //最后的一个较小的块。
    ++ block_num;
    L[block_num] = R[block_num - 1] + 1;
    R[block_num] = n;
  }
  //分配元素所属的块编号。
  for (int i = 1; i <= block_num; ++ i) {
    for (int j = L[i]; j <= R[i]; ++ j) {
      bel[j] = i;
      sum[i] += a[j]; //预处理区间和
    }
  }
}
void Modify(int L_, int R_, int val_) {
  int bell = bel[L_], belr = bel[R_];
  if (bell == belr) {
    for (int i = L_; i <= R_; ++ i) {
      a[i] += val_;
      sum[bell] += val_;
    }
    return ;
  }
  for (int i = bell + 1; i <= belr - 1; ++ i) tag[i] += val_;
  for (int i = L_; i <= R[bell]; ++ i) {
    a[i] += val_;
    sum[bell] += val_;
  }
  for (int i = L[belr]; i <= R_; ++ i) {
    a[i] += val_;
    sum[belr] += val_;
  }
}
LL Query(int L_, int R_, int mod_) {
  int bell = bel[L_], belr = bel[R_], ret = 0;
  if (bell == belr) {
    for (int i = L_; i <= R_; ++ i) ret = (ret + a[i] + tag[bell]) % mod_;
    return ret;
  }
  for (int i = bell + 1; i <= belr - 1; ++ i) {
    ret = (ret + sum[i] + (R[i] - L[i] + 1) * tag[i] % mod_) % mod_;
  }
  for (int i = L_; i <= R[bell]; ++ i) ret = (ret + a[i] + tag[bell]) % mod_;
  for (int i = L[belr]; i <= R_; ++ i) ret = (ret + a[i] + tag[belr]) % mod_;
  return ret;
}
//=============================================================
int main() { 
  n = read();
  for (int i = 1; i <= n; ++ i) a[i] = read();
  PrepareBlock();
  for (int i = 1; i <= n; ++ i) {
    int opt = read(), l = read(), r = read(), c = read();
    if (opt == 0) {
      Modify(l, r, c);
    } else {
      printf("%lld\n", Query(l, r, c + 1));
    }
  }
  return 0; 
}
练习
建议阅读：LibreOJ 数列分块入门 1 ~ ⑨。
包含下列 9 个经典题目，涉及了数列分块的大部分重要思想：

区间加，单点查询：基础模板。
区间加，区间查询小于给定值 元素数：维护单调性。
区间加，区间查询小于给定值 最大元素：维护单调性。
区间加，区间求和：基础模板，最简单的区间信息合并。
区间开方，区间求和：复杂度分析。
单点插入，单点查询：复杂度分析，块状数组。
区间加，区间乘，单点查询：较复杂的区间信息合并。
区间赋值，查询区间等于给定值元素数：复杂度分析。
查询区间最小众数：复杂区间信息的预处理，复杂的区间信息合并。
均值法复杂度分析
引入
在上述例题区间和中，修改操作与查询操作的复杂度是平衡的，因此可以简单地将块大小设为 \(\sqrt{n}\)。
但在某些数列分块的题目中，会出现修改查询操作复杂度并不平衡的状况，此时需要通过计算得到最优的块大小。

设数列长度为 \(n\)，查询次数为 \(m\)，单次修改复杂度 \(O(p)\)，单次查询复杂度 \(O(q)\)，\(p,q\) 的大小均与块大小相关。
总复杂度一般可以表示成这种形式：\(O(np + mq)\)。
根据高中必修 1 的均值不等式，可知 \(np + mq\ge 2\sqrt{nmpq}\)，当且仅当 \(np=mq\) 时，等号成立，复杂度最低。
即可解得最优的块大小。

确定最优块大小
P5356 [Ynoi2017] 由乃打扑克

给定一长度为 \(n\) 的数列，有 \(n\) 次操作。
操作分为两种：区间加，查询区间第 \(k\) 大。
\(1\le n,m\le 10^5\)。
2S，128MB。

首先有个超级暴力的做法：
区间加不影响区间内大小关系，考虑维护每块排序后的序列。
修改时整块打标记，散块修改后重构排序后序列。
查询时二分答案判定，散块暴力，整块内二分。

设块大小为 \(T\)，单次修改复杂度为 \(O(\frac{n}{T} + T\log n)\)，单次查询复杂度为 \(O((\frac{n}{T}\log n+T)\log n)\)。
单次询问复杂度严格大于修改复杂度，则总复杂度为 \(O(n(\frac{n}{T}\log^2 n +T\log n))\)。
由均值不等式，\(\frac{n}{T}\log^2 n +T\log n\ge 2\sqrt{n\log n}\log n\)，当且仅当 \(\frac{n}{T}\log^2 n =T\log n\) 时等号成立，复杂度最低。

此时块大小 \(T = \sqrt{n\log n}\)，总复杂度 \(O(n\sqrt{n\log n}\log n)\)。

当然这个做法是过不去的，考虑更优秀的做法。

发现修改操作时，重构散块不需要重新排序。
将端点所在块分为两部分：需要被修改的，不需要被修改的。
修改后，各部分内部分别有序，元素大小关系不变。
考虑直接归并，单次修改复杂度变为 \(O(\frac{n}{T} + T)\)。

询问时，考虑将两个散块先归并成一个有序的数列，再进行二分。
这样对散块部分的查询也可以二分，单次查询复杂度变为 \(O(\frac{n}{T}\log^2 n + \log^2 n + T)\)。

单次询问复杂度仍严格大于修改复杂度，则总复杂度为 \(O(n(\frac{n}{T}\log^2 n +T))\)。
由均值不等式，\(\frac{n}{T}\log^2 n +T\ge 2\sqrt{n}\log n\)，当且仅当 \(\frac{n}{T}\log^2 n =T\) 时等号成立，复杂度最低。

此时块大小 \(T = \sqrt{n}\log n\)，总复杂度 \(O(n\sqrt{n}\log n)\)。
然后卡亿点常就可以过啦！

莫队的复杂度
设序列长度为 \(n\)，询问次数为 \(m\)，假设可以 \(O(1)\) 地处理端点的移动 和 回答询问。
考虑莫队算法中对询问的排序过程：
先按照左端点的块编号升序排序，左端点在同一块中的按右端点升序排序。
设块大小为 \(T\)，排序后将询问分为了 \(\frac{n}{T}\) 块，每块内右端点单调递增。

考虑每一块的右端点单调递增，移动的复杂度为 \(O(n)\)。
右端点的垮块移动量上界为 \(O(n)\)，则右端点移动的总复杂度为 \(O(\frac{n^2}{T})\)。
对于块内的每一次询问，左端点移动量 \(\le T\)。
垮块移动左端点的改变量为 \(T\)，则左端点移动的总复杂度为 \(O(mT)\)。

算法的总复杂度为 \(O(\frac{n^2}{T}+mT + m)\)，由均值不等式，\(\frac{n^2}{T}+mT\ge 2\sqrt{n^2m}\)，当且仅当 \(\frac{n^2}{T}=mT\) 时，复杂度最低。
解得最优块大小为 \(\frac{n}{\sqrt{m}}\)，算法总复杂度为 \(O(n\sqrt{m} + m)\)。

如果简单将块大小设为 \(\sqrt n\)，得算法总复杂度为 \(O(n\sqrt n + m\sqrt n + m)\)。
与上面得到的最优复杂度作差，得：

\[n\sqrt{n} + m\sqrt{n} - n\sqrt{m}= n(\sqrt{n} + \frac{m}{\sqrt{n}} - \sqrt{m})
\]

考虑括号内的三项，由均值不等式，有：

\[\sqrt{n} + \dfrac{m}{\sqrt{n}} -\sqrt{m} \ge 2\sqrt{m} - \sqrt{m} = \sqrt{m} > 0
\]

得块大小设为 \(\sqrt n\) 劣于块大小为 \(\frac{n}{\sqrt{m}}\)。

平衡结合
引入
考虑这样一个问题：维护数列，支持单点修改，区间求和。
显然可以线段树，树状数组求解，它们查询修改的是平衡的，均为 \(O(\log n)\) 级别。
可以在修改，查询次数同级时获得较优的时间复杂度。

但修改与查询次数可能是不平衡的，这时可以通过别的手段来处理该问题：
考虑分块解法，修改 \(O(1)\)，查询 \(O(\sqrt{n})\) ，在修改数大于查询数时，可以获得更优的时间复杂度。
若查询次数远大于修改次数，甚至可以考虑直接维护前缀和，修改 \(O(n)\)，但查询的复杂度仅为 \(O(1)\)。

这就是一种平衡结合。
根据修改与查询次数的关系，通过调整维护的手段，使总的复杂度达到更低级别。

例一
bzoj3809. Gty的二逼妹子序列

给定一长度为 \(n\) 的数列 \(a\)，\(m\) 次询问。
每次询问给定参数 \(l,r,a,b\)，求区间 \([l,r]\) 内权值 \(\in [a,b]\) 的数的种类数。
\(1\le a_i\le n\le 10^5\)，\(1\le m\le 10^6\)。

发现莫队比较便于维护种类数，套一个莫队消去区间的限制。
考虑值域的限制，权值线段树进行维护。
单次 修改/查询 复杂度均为 \(O(\log n)\)。
设块大小为 \(\dfrac{n}{\sqrt{m}}\)，总复杂度为 \(O(n\sqrt{m}\log n + m\log n)\)。

发现修改和查询的次数并不平均，而线段树查询修改的复杂度是平均的。
考虑能否替换成另一种 修改复杂度较小，查询复杂度较大的数据结构。
想到直接使用数组进行O1修改On查询

只有单点修改，考虑对值域分块，维护块内不同的数的个数，可在莫队左右端点移动顺便维护。
查询时，在查询值域内的完整块直接统计答案，不完整块暴力查询。
设块大小为 \(\dfrac{n}{\sqrt{m}}\)，单次修改复杂度 \(O(1)\)，查询复杂度 \(\sqrt{n}\)，总复杂度为 \(O(n\sqrt{m} +m\sqrt{n})\)。

代码

//知识点：莫队，分块 
/*
By:Luckyblock
*/
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#define ll long long
const int kMaxn = 1e5 + 10;
const int kMaxm = 1e6 + 10;
const int kMaxSqrtn = 320 + 10;
//=============================================================
struct Que {
  int l, r, a, b, id;
} q[kMaxm];
int n, m, a[kMaxn];
int block_size, block_num, L[kMaxn], R[kMaxn], bel[kMaxn];
int nowl = 1, nowr, cnt[kMaxn], sum[kMaxSqrtn];
int ans[kMaxm];
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void GetMax(int &fir_, int sec_) {
  if (sec_ > fir_) fir_ = sec_;
}
void GetMin(int &fir_, int sec_) {
  if (sec_ < fir_) fir_ = sec_;
}
bool CompareQuery(Que fir, Que sec) {
  if (bel[fir.l] != bel[sec.l]) return bel[fir.l] < bel[sec.l];
  return fir.r < sec.r;
}
void Prepare() {
  n = read(), m = read();
  for (int i = 1; i <= n; ++ i) a[i] = read();
  for (int i = 1; i <= m; ++ i) {
    q[i] = (Que) {read(), read(), read(), read(), i};
  }
  block_size = (int) sqrt(n), block_num = n / block_size;
  for (int i = 1; i <= block_num; ++ i) {
    L[i] = (i - 1) * block_size + 1;
    R[i] = i * block_size;
  }
  if (R[block_num] < n) {
    L[++ block_num] = R[block_num - 1] + 1;
    R[block_num] = n;
  } 
  
  for (int j = 1; j <= block_num; ++ j) {
    for (int i = L[j]; i <= R[j]; ++ i) {
      bel[i] = j;
    }
  }
  std :: sort(q + 1, q + m + 1, CompareQuery);
}
int Query(int l_, int r_) {
  int ret = 0;
  if (bel[l_] == bel[r_]) {
    for (int i = l_; i <= r_; ++ i) ret += (cnt[i] > 0);
    return ret;
  }
  for (int i = bel[l_] + 1; i <= bel[r_] - 1; ++ i) {
    ret += sum[i];
  }
  for (int i = l_; i <= R[bel[l_]]; ++ i) ret += (cnt[i] > 0);
  for (int i = L[bel[r_]]; i <= r_; ++ i) ret += (cnt[i] > 0);
  return ret;
}
void Delete(int now_) {
  cnt[a[now_]] --;
  if (! cnt[a[now_]]) sum[bel[a[now_]]] --;
}
void Add(int now_) {
  if (! cnt[a[now_]]) sum[bel[a[now_]]] ++;
  cnt[a[now_]] ++;
}
//=============================================================
int main() {
  Prepare();
  for (int i = 1; i <= m; ++ i) {
    int l = q[i].l, r = q[i].r, a = q[i].a, b = q[i].b, id = q[i].id;
    while (nowl < l) Delete(nowl), nowl ++;
    while (nowl > l) nowl --, Add(nowl);
    while (nowr > r) Delete(nowr), nowr --;
    while (nowr < r) nowr ++, Add(nowr);
    ans[q[i].id] = Query(a, b);
  }
  for (int i = 1; i <= m; ++ i) printf("%d\n", ans[i]);
  return 0;
}
例二
可能是集训题的无出处题

给定一长度为 \(n\) 的数列 \(a\)，参数 \(w\)，\(q\) 次询问。
每次询问给定参数 \(l,r\)，求忽略出现次数 \(>w\) 的数后，区间 \([l,r]\) 内第 \(k\) 小值。
\(1\le n,q,a_i,w\le10^5\)。

忽略出现次数 \(>w\) 的数，没法上主席树。
但显然可以莫队套平衡树，当枚举的区间内某个数首次出现时插入，出现次数 \(=0\) 或 \(> w\) 时删除。

\(n,a_i\) 同级，修改和查询的复杂度相同，均为 \(O(\log n)\)。
块大小为 \(T\) 时，总复杂度为 \(O((\frac{n^2}{T}+qT)\log n + q\log n)\)。
块大小为 \(\frac{n}{\sqrt{q}}\) 时最优，总复杂度为 \(O(n\sqrt{q}\log n+ q\log n)\)，过不了。

发现块大小为 \(T\) 时，莫队中一共有 \(\frac{n^2}{T}+qT\) 次修改操作，但只有 \(q\) 次查询操作。
考虑平衡结合，按照上述方法，使用分块维护区间第 \(k\) 小值。
单次修改复杂度变为 \(O(1)\)，查询变为 \(O(\sqrt{n})\)，总复杂度 \(O(\frac{n^2}{T}+qT + q\sqrt{n})\)。
块大小取 \(\frac{n}{\sqrt{q}}\) 时最优，总复杂度为 \(O(n\sqrt{q} + q\sqrt{n})\)。

代码见这个金牌爷的博客：WerKeyTom_FTD。

预处理之王
引入
字面意思，通过预处理，合并完整块的信息，从而避免在查询时对信息的合并，以降低时间复杂度。
因为有些预处理手段十分神仙，处理对象复杂，处理方式神奇，而且为了总的时间复杂度不择手段。
所以把这种处理手段称为 预处理之王。

例一
简单的预处理

「hackerrank」Range Modular Queries

给定一长度为 \(n\) 的数列 \(a\)，\(q\) 次询问。
每次询问给定参数 \(l,r,x,y\)，求：

\[\sum_{i=l}^{r} [a_i \bmod x = y]
\]

\(1\le n,q,a_i\le 5\times 10^4\)。

数据范围比较喜人，\(n,q,a_i\) 同级，先考虑暴力。
考虑莫队搞掉区间限制，维护当前区间内各权值出现的次数。
设 \(cnt_{i}\) 表示当前区间内权值 \(i\) 出现的次数，显然答案为：

\[\sum_{k = 1}cnt_{y+kx}
\]

复杂度 \(O(\text{Unknowen})\)，过不了。

发现上述的算法查询复杂度与 \(x\) 有关。
当 \(x\) 较小时，查询复杂度较高，可达到 \(O(n)\) 级别。\(x\) 较大时复杂度较优秀。
考虑根号分治，对模数 \(x\le 200\) 和 \(x > 200\) 的询问分开考虑。

对于 \(x\le 200\) 的询问，考虑分块。
设块大小为 \(\sqrt{n}\)，预处理 \(f_{i,j,k}\) 表示前 i 个块中，% j = k 的数的个数。
预处理复杂度上界 \(O(200^3) \approx O(n\sqrt{n})\)。
询问时整块直接 \(O(1)\) 查询预处理的前缀和，散块暴力。
单次查询复杂度 \(O(\sqrt{n})\)。

对于 \(x> 200\) 的询问，套用上述莫队算法即可。
单次查询复杂度上界为 \(O(200) \approx O(\sqrt{n})\) 级别。

\(n,q\) 同级，总复杂度约为 \(O(n\sqrt{n})\) 级别，可过。

这同时也是一个平衡结合的例子，通过根号分治使时间复杂度达到平衡。

代码

//知识点：分块，莫队 
/*
By:Luckyblock
*/
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#define ll long long
const int kMaxn = 4e4 + 10;
const int kMaxSqrtn = 210;
//=============================================================
struct Query {
  int l, r, mod, val, id;
} q[kMaxn];
int n, m, qnum, maxa, a[kMaxn], ans[kMaxn];
int block_size, block_num, sqrt_maxa, L[kMaxSqrtn], R[kMaxSqrtn], bel[kMaxn];
int f[kMaxSqrtn][kMaxSqrtn][kMaxSqrtn]; //f[i][j][k]：前 i 个块，% j = k 的数的个数。 
int nowl = 1, nowr, cnt[kMaxn]; //注意端点的初值 
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void Getmax(int &fir_, int sec_) {
  if (sec_ > fir_) fir_ = sec_;
}
void Getmin(int &fir_, int sec_) {
  if (sec_ < fir_) fir_ = sec_;
}
void Debug() {
  printf("%d %d\n***********\n", block_size, block_num);
  for (int i = 1; i <= block_num; ++ i) {
    for (int j = 1; j <= block_size; ++ j) {
      for (int k = 0; k < j; ++ k) {
        printf("1~%d mod %d = %d appear %d times\n", i, j, k, f[i][j][k]);
      }
    }
  }
}
void PrepareBlock() {
  block_size = (int) sqrt(n);
  block_num = n / block_size;
  for (int i = 1; i <= block_num; ++ i) {
    L[i] = (i - 1) * block_size + 1;
    R[i] = i * block_size;
  }
  if (R[block_num] < n) {
    ++ block_num;
    L[block_num] = R[block_num - 1] + 1;
    R[block_num] = n;
  }
  for (int i = 1; i <= block_num; ++ i) {
    for (int j = L[i]; j <= R[i]; ++ j) {
      bel[j] = i;
    }
  }
  
  sqrt_maxa = (int) sqrt(maxa);
  for (int i = 1; i <= block_num; ++ i) {
    for (int j = 1; j <= sqrt_maxa; ++ j) {
      for (int k = L[i]; k <= R[i]; ++ k) {
        f[i][j][a[k] % j] ++;
      }
    }  
  }
  for (int i = 1; i <= block_num; ++ i) {
    for (int j = 1; j <= sqrt_maxa; ++ j) {
      for (int k = 0; k < j; ++ k) {
        f[i][j][k] += f[i - 1][j][k];
      }
    }
  }
//  Debug();
}
bool CompareQuery(Query fir_, Query sec_) {
  if (bel[fir_.l] != bel[sec_.l]) return bel[fir_.l] < bel[sec_.l];
  return fir_.r < sec_.r;
}
void Solve(int l_, int r_, int mod_, int val_, int id_) {
  if (bel[l_] == bel[r_]) {
    for (int i = l_; i <= r_; ++ i) {
      ans[id_] += (a[i] % mod_ == val_);
    }
    return ;
  }
  int bell = bel[l_], belr = bel[r_];
  ans[id_] += f[belr - 1][mod_][val_] - f[bell][mod_][val_];
  for (int i = l_; i <= R[bell]; ++ i) {
    ans[id_] += (a[i] % mod_ == val_);
  }
  for (int i = L[belr]; i <= r_; ++ i) {
    ans[id_] += (a[i] % mod_ == val_);
  }
}
void Add(int pos_) {
  cnt[a[pos_]] ++;
}
void Del(int pos_) {
  cnt[a[pos_]] --;
}
//=============================================================
int main() {
  n = read(), m = read();
  for (int i = 1; i <= n; ++ i) {
    a[i] = read();
    Getmax(maxa, a[i]); 
  }
  PrepareBlock();
  
  for (int i = 1; i <= m; ++ i) {
    int l = read() + 1, r = read() + 1;
    int mod = read(), val = read();
    if (mod <= sqrt_maxa) {
      Solve(l, r, mod, val, i);
    } else {
      q[++ qnum] = (Query) {l, r, mod, val, i};  
    }
  }
  
  std :: sort(q + 1, q + qnum + 1, CompareQuery);
  for (int i = 1; i <= qnum; ++ i) {
    int l = q[i].l, r = q[i].r, mod = q[i].mod, val = q[i].val;
    while (nowl > l) -- nowl, Add(nowl);
    while (nowr < r) ++ nowr, Add(nowr);
    while (nowl < l) Del(nowl), ++ nowl;
    while (nowr > r) Del(nowr), -- nowr;
    for (int j = val; j <= maxa; j += mod) {
      ans[q[i].id] += cnt[j];
    }
  }
  for (int i = 1; i <= m; ++ i) printf("%d\n", ans[i]);
  return 0;
}
例二
bzoj3744. Gty的妹子序列

给定一长度为 \(n\) 的数列 \(a\)，\(m\) 次查询操作。
每次查询给定参数 \(l,r\)，求区间 \([l,r]\) 内的逆序对数。
强制在线。
\(1\le n,m\le 5\times 10^4\)，\(1\le a_i\le 2^{31}-1\)。

不强制在线是 CDQ 傻逼题。
强制在线，没有什么方便的数据结构维护，考虑分块。

这是一开始的想法：
按块大小为 \(\sqrt{n}\) 分块，树状数组暴力预处理每块的逆序对数，复杂度 \(O(\sqrt {n}\sqrt {n}\log \sqrt{n}) = O(n\log \sqrt{n})\)。
考虑单次查询的过程，发现可拆分为下面几个部分：

整块内的逆序对数，已预处理得到，查询复杂度 \(O(\dfrac{n}{\sqrt{n}}) = O(\sqrt{n})\)。
散块内的逆序对数，树状数组暴力即可，复杂度 \(O(\sqrt{n}\log \sqrt{n})\)。
整块与整块间的逆序对。
散块与整块间的逆序对。
考虑如何得到上述 3,4 两项的贡献。

发现预处理整块之间的逆序对数时，需要遍历整个序列。
太浪费了！考虑顺便预处理第 3 项。
设 \(f_{l,r}\) 表示整块 \(l\sim r\) 的逆序对数。
对每个块都维护一个权值树状数组，在枚举到块 \(j\) 的某元素时，枚举之前块的树状数组。
设枚举到块 \(i\)，查询比该元素大的数的个数，即为当前元素 与 块 \(i\) 的逆序对数，累加到 \(f_{j,i}\) 中。
这样做完后，\(f_{i,j}\) 存的只是块 \(i\) 和块 \(j\) 的逆序对数，DP 处理 \(f\)，有转移：

\[f_{i,j} = f_{i,j} + f_{i,j-1} + \sum_{k=i+1}^{j}{f_{k,j}}
\]

需要枚举每块的每一个数再枚举所有之前的块再在树状数组中查询。
总复杂度为 \(O(\sqrt{n}\sqrt{n}\sqrt{n}\log\sqrt{n}) = O(n\sqrt{n}\log\sqrt{n})\)。
是不是很扯淡

考虑第 4 项，由于散块较小，考虑直接枚举散块元素。
对于右侧散块，即查询整块中比它大的数的个数。
考虑主席树维护，左侧散块同理，查询比它小的数的个数即可。
复杂度 \(O(\sqrt{n}\log n)\)。

累计一下，总复杂度为 \(O(n\sqrt{n}\log\sqrt{n} +m\sqrt{n}\log n)\)，\(n,m\) 同级，为 \(O(n\sqrt{n}\log n)\) 级别，瓶颈似乎在主席树上。

细节比较多，调调调过了几组手玩的数据，交上去 T 了。
常数过大被卡了。

发现预处理并不是复杂度瓶颈。
且得到的信息并不丰富，仅求出了连续的块的逆序对，dp 数组的大小仅为 \(O(\sqrt{n}\sqrt{n})=
O(n)\) 级别。
而预处理过程中枚举到了所有元素，且求出了它与之前所有块的逆序对数，却把信息压缩成这样，这显然不大合适。

考虑修改预处理对象，设 \(f_{l,r}\) 表示，从块 \(l\) 的开头，到 位置 \(r\) 的逆序对数。
预处理时枚举所有块，从它的开头，一直扫到整个数列的尾部，暴力用树状数组求逆序对。
复杂度 \(O(n\sqrt{n}\log n)\)。

再考虑单次查询时的 4 部分：

整块内的逆序对数。
散块内的逆序对数。
整块与整块间的逆序对。
散块与整块间的逆序对。
查询时，可直接得到第一个整块到查询区间右端点的逆序对数，第 1,3 项复杂度变为 \(O(1)\)，且同时得到了右侧散块与它自身，与整块的逆序对数。

发现仅剩左侧散块与它自身，与整块的逆序对了。
考虑合并 2,4 两项，直接用主席树求。
枚举左侧散块中所有数，查询从 该数到右端点 内，比它大的数的个数。
复杂度 \(O(\sqrt{n}\log n)\)。

总复杂度不变，仍为 \(O(n\sqrt{n}\log n)\)，但通过增大预处理的复杂度，减小了查询的巨大常数。

然后就可过了。

还有 \(O(n\sqrt n)\) 的预处理之王做法，通过归并来进行实现。
感觉比较神，建议阅读题解学习，之后再补。

代码

//知识点：分块 
/*
By:Luckyblock
*/
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define ll long long
const int kMaxm = 5e5;
const int kMaxn = 5e5 + 10;
const int kMaxSqrtn = 230 + 10;
//=============================================================
int n, m, block_size, block_num;
int root[kMaxn];
int maxa, map[kMaxn], a[kMaxn], data[kMaxn];
int bel[kMaxn], L[kMaxSqrtn], R[kMaxSqrtn], f[kMaxSqrtn][kMaxn];
//=============================================================
inline int read() {
  int f = 1, w = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0');
  return f * w;
}
void GetMax(int &fir_, int sec_) {
  if (sec_ > fir_) fir_ = sec_;
}
void GetMin(int &fir_, int sec_) {
  if (sec_ < fir_) fir_ = sec_;
}
//ScientificConceptOfDevelopmentTree
namespace HjtTree{
  #define ls (lson[now_])
  #define rs (rson[now_])
  #define mid (L_+R_>>1)
  int node_num, lson[kMaxn << 4], rson[kMaxn << 4], size[kMaxn << 4];
  void Insert(int &now_, int pre_, int L_, int R_, int val_) {
	  now_ = ++ node_num;
	  size[now_] = size[pre_] + 1;
	  ls = lson[pre_], rs = rson[pre_];
	  if (L_ == R_) return ;
	  if (val_ <= mid) Insert(ls, lson[pre_], L_, mid, val_);
	  else Insert(rs, rson[pre_], mid + 1, R_, val_);
  }
  int Query(int r_, int l_, int L_, int R_, int ql_, int qr_) {
	  if (ql_ > qr_) return 0;
    if (ql_ <= L_ && R_ <= qr_) return size[r_] - size[l_];
	  int ret = 0;
    if (ql_ <= mid) ret += Query(lson[r_], lson[l_], L_, mid, ql_, qr_);
	  if (qr_ > mid) ret += Query(rson[r_], rson[l_], mid + 1, R_, ql_, qr_);
    return ret;
  }
}
struct TreeArray {
  #define lowbit(x) (x&-x)
  int time, ti[kMaxm + 10], t[kMaxm + 10];
  void Clear () {
    time ++;
  }
  void Add(int pos_, int val_) {
    for (; pos_ <= maxa; pos_ += lowbit(pos_)) {
      if (ti[pos_] != time) {
        t[pos_] = 0;
        ti[pos_] = time;
      }
      t[pos_] += val_;
    }
  }
  int Sum(int pos_) {
    int ret = 0;
    for (; pos_; pos_ -= lowbit(pos_)) {
      if (ti[pos_] != time) {
        t[pos_] = 0;
        ti[pos_] = time;
      }
      ret += t[pos_];
    }
    return ret;
  }
} tmp;
void Prepare() {
  n = read();
  for (int i = 1; i <= n; ++ i) {
    a[i] = data[i] = read();
  }
  data[0] = - 0x3f3f3f3f;
  std :: sort(data + 1, data + n + 1);
  for (int i = 1; i <= n; ++ i) {
    if (data[i] != data[i - 1]) maxa ++;
    data[maxa] = data[i];
  }
  for (int i = 1; i <= n; ++ i) {
    int ori = a[i];
    a[i] = std :: lower_bound(data + 1, data + maxa + 1, ori) - data;
    map[a[i]] = ori;
  }
}
void PrepareBlock() {
  int i = 1;
  block_size = (int) sqrt(n);
  block_num = n / block_size;
  for (i = 1; i <= block_num; ++ i) {
    L[i] = (i - 1) * block_size + 1;
    R[i] = i * block_size;
  }
  if (R[block_num] < n) {
    L[++ block_num] = R[block_num - 1] + 1;
    R[block_num] = n;
  } 
  
  for (int j = 1; j <= block_num; ++ j) {
    for (int i = L[j]; i <= R[j]; ++ i) {
      bel[i] = j;
    }
  }
  for (int l = 1; l <= block_num; ++ l) {
    tmp.Clear();
    for (int r = L[l]; r <= n; ++ r) {
      f[l][r] = f[l][r - 1] + tmp.Sum(maxa) - tmp.Sum(a[r]);
      tmp.Add(a[r], 1);
    }
  }
}
//=============================================================
int main() {
  Prepare();
  PrepareBlock();
  for (int i = 1; i <= n; ++ i) {
    HjtTree :: Insert(root[i], root[i - 1], 1, maxa, a[i]);
  }
  m = read();
  int lastans = 0;
  while (m --) {
    int l = read() ^ lastans, r = read() ^ lastans;
    lastans = 0;
    if (l > r) {
      printf("0\n");
      continue ;
    }
    if (bel[l] == bel[r]) {
      tmp.Clear();
      for (int i = l; i <= r; ++ i) {
        lastans += tmp.Sum(maxa) - tmp.Sum(a[i]);
        tmp.Add(a[i], 1);
      }
      printf("%d\n", lastans);
      continue ;
    }
    lastans = f[bel[l] + 1][r]; 
    for (int i = l; i <= R[bel[l]]; ++ i) {
      lastans += HjtTree :: Query(root[r], root[i], 1, maxa, 1, a[i] - 1);
    }
    printf("%d\n", lastans);
  }
  return 0;
}