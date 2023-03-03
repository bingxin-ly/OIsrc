#include <bits/stdc++.h>
using namespace std;

const int MAX = 5e5 + 10;
int n, // 树状数组的实际长度
    m;
int tree_array[MAX], src[MAX];

inline int lowbit(int x) { return x & -x; }

int query(int x) // 求差分上的前缀和
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += tree_array[x];
    return ret;
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