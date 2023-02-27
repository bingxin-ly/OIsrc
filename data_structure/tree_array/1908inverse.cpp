// 加强之后的数据有可能重复，记得比较时判重~
#include <bits/stdc++.h>
using namespace std;

const int MAX = 5e5 + 10;
struct num
{
    int id, val;
    bool operator<(const num &other) const
    {
        return val != other.val ? (val > other.val) : (id > other.id);
    }
} src[MAX];
int n, tree_array[MAX], mp[MAX];

inline int lowbit(int x) { return x & -x; }

int query(int x)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += tree_array[x];
    return ret;
}
inline void add(int pos, int val)
{
    for (; pos <= n; pos += lowbit(pos))
        tree_array[pos] += val;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> src[i].val, src[i].id = i;
    sort(src + 1, src + n + 1);

    size_t ans = 0;
    for (int i = 1; i <= n; i++)
    {
        add(src[i].id, 1);
        ans += query(src[i].id - 1);
    }
    cout << ans;
    return 0;
}

bool cmp(num a, num b)
{
    return a.val != b.val ? (a.val < b.val) : (a.id < b.id);
}
int main_other()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> src[i].val, src[i].id = i;
    sort(src + 1, src + n + 1, cmp);

    for (int i = 1; i <= n; i++)
        mp[src[i].id] = i;

    /* 记录在第i个数之前有几个数比它小或等于他，ai<=aj且i<=j
    那么我们就要删除这些数。用i−sum(value[i])即可*/
    size_t ans = 0;
    for (int i = 1; i <= n; i++)
    {
        add(mp[i], 1);
        ans += i - query(mp[i]);
    }
    cout << ans;
    return 0;
}