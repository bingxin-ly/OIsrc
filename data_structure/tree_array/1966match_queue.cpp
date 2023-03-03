#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10, MOD = 1e8 - 3;
struct torch
{
    int id, height;
    bool operator<(const torch &other) const { return height < other.height; }
} src1[MAX], src2[MAX];
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
        cin >> src1[i].height, src1[i].id = i;
    for (int i = 1; i <= n; i++)
        cin >> src2[i].height, src2[i].id = i;
    sort(src1 + 1, src1 + n + 1);
    sort(src2 + 1, src2 + n + 1);

    for (int i = 1; i <= n; i++)
        mp[src2[i].id] = src1[i].id;

    size_t ans = 0;
    for (int i = 1; i <= n; i++)
    {
        add(mp[i], 1);
        ans += i - query(mp[i]);
        ans %= MOD;
    }
    cout << ans;
    return 0;
}
