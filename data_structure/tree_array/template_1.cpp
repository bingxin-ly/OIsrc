// 前缀和，维护单点加区间和
#include <bits/stdc++.h>
using namespace std;

const int MAX = 500010;
int n, // 树状数组的实际长度
    m, src[MAX];
int tree_array[MAX], sum[MAX];

inline int lowbit(int x) { return x & -x; }
int prefix_sum(int x)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += tree_array[x];
    return ret;
}

void build_t()
{
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + src[i];
        tree_array[i] = sum[i] - sum[i - lowbit(i)];
        /* 求原数组前缀和，再更新线段树 O(n) */
    }
}
void build_m()
{
    for (int i = 1; i <= n; i++)
    {
        tree_array[i] += src[i];
        int j = i + lowbit(i);
        if (j <= n)
            tree_array[j] += tree_array[i];
        /*每一个节点的值是由所有与自己直接相连的儿子的值求和得到的。
        因此可以倒着考虑贡献，即每次确定完儿子的值后，用自己的值更新自己的直接父亲*/
    }
}
inline int query(int l, int r)
{
    // 求前缀和
    return prefix_sum(r) - prefix_sum(l - 1);
}
void add(int pos, int val)
{
    for (; pos <= n; pos += lowbit(pos))
        tree_array[pos] += val;
}

int main()
{
    cin >> n >> m;
    /* for (int i = 1, original; i <= n; i++)
        cin >> original, add(i, original); // 建树：n次修改 O(nlogn) */
    for (int i = 1; i <= n; i++)
        cin >> src[i];
    build_t();
    int op, a, b;
    for (int i = 1; i <= m; i++)
    {
        cin >> op >> a >> b;
        if (op == 1)
            add(a, b);
        else
            cout << query(a, b) << endl;
    }
    return 0;
}