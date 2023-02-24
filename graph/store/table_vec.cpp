struct edge
{
    int to, w;
};
vector<edge> graph[MAX];

inline void add(int u, int v, int w = 1)
{
    graph[u].push_back({v, w});
}

int main()
{
    cin >> n;
    for (int i = 1, u, v, w; i <= n; i++)
    {
        cin >> u >> v >> w;
        add(u, v, w);
    }
    return 0;
}