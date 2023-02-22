#include <bits/stdc++.h>
using namespace std;

const int MAX = 0;

struct edge
{
    int to, w;
};
vector<edge> graph[MAX];
int n;

inline void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}

int main()
{
    cin >> n;
    int u, v, w;
    for (int i = 1; i <= n; i++)
    {
        cin >> u >> v >> w;
        add(u, v, w);
    }
    return 0;
}