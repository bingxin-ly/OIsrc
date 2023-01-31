#include <bits/stdc++.h>
using namespace std;

const int LEN = 500010;
int n, // 树状数组的实际长度
    m;
int tree_array[LEN];

inline int lowbit(int x)
{
    return x & -x;
}
int prefix_sum(int x)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += tree_array[x];
    return ret;
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
    for (int i = 1, original; i <= n; i++)
        cin >> original, add(i, original);
    int op, a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> op >> a >> b;
        if (op == 1)
            add(a, b);
        else
            cout << query(a, b) << endl;
    }
    return 0;
}