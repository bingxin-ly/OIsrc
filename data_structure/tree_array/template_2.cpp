#include <bits/stdc++.h>
using namespace std;

const int LEN = 500010;
int n, // 树状数组的实际长度
    m;
int tree_array[LEN], src[LEN];

inline int lowbit(int x)
{
    return x & -x;
}
// 求前缀和
int prefix_sum(int x)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += tree_array[x];
    return ret;
}
inline int query(int pos)
{
    return prefix_sum(pos);
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
        cin >> src[i];
    int op, a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> op;
        if (op == 1)
            cin >> a >> b >> c,
                add(a, c), add(b + 1, -c);
        else
            cin >> a,
                cout << query(a) + src[a] << endl;
    }
    return 0;
}