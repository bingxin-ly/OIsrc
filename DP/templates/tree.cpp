#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> int_pair;
const int MAX = 6e3 + 10;

bool has_fa[MAX];
int n, happy[MAX], f[MAX][2];
vector<int_pair> graph[MAX];

void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}
void dfs(int u)
{
    f[u][1] = happy[u];

    for (auto i : graph[u])
    {
        int j = i.first;
        dfs(j);

        f[u][0] += max(f[j][0], f[j][1]);
        f[u][1] += f[j][0];
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> happy[i];

    int l, k;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> l >> k;
        has_fa[l] = true;
        add(k, l);
    }

    int root = 1;
    while (has_fa[root])
        root++; // 获取父节点

    dfs(root);

    cout << max(f[root][0], f[root][1]);
    return 0;
}