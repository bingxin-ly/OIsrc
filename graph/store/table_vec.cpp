#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> int_pair;
const int MAX = 1e3; // TODO

int n;
vector<int_pair> graph[MAX];

void add(int u, int v, int w = 1)
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