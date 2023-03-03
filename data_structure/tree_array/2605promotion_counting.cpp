#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10;
struct cow
{
    int id, power;
    bool operator<(const cow &other) const { return power < other.power; }
} cows[MAX];
int n, power[MAX], tree_array[MAX], mp[MAX], ans[MAX];

vector<int> graph[MAX];
inline void add_edge(int u, int v) { graph[u].push_back(v); }

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
void dfs(int u)
{
    ans[u] = -(query(n) - query(mp[u]));
    for (auto i : graph[u])
        dfs(i);
    ans[u] += (query(n) - query(mp[u]));
    add(mp[u], 1);
    /* 在递归子树之前先把答案减掉，递归完子树后再把新的答案加回来，这样结果就是正确的了! */
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> cows[i].power, cows[i].id = i;
    cows[1].id = 1;
    for (int i = 2, up; i <= n; i++)
        cin >> up, add_edge(up, i);

    sort(cows + 1, cows + n + 1);
    for (int i = 1; i <= n; i++)
        mp[cows[i].id] = i;

    dfs(1);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << endl;
    return 0;
}
