#include <bits/stdc++.h>
using namespace std;
vector<int> head[100];
stack<int> st;
bool vis[100];

void dfs(int n)
{
    st.push(n);
    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        vis[u] = true;
        cout << u << endl;
        int sz = head[u].size();
        for (int i = sz - 1; i > 0; i--)
        {
            int v = head[u][i];
            if (!vis[v])
            {
                st.push(v);
                vis[v] = true;
            }
        }
    }
}
void add(int u, int v)
{
    head[v].push_back(u);
    head[u].push_back(v);
}
int main()
{
    int m;
    cin >> m;
    for (int i = 0, u, v; i < m; i++)
    {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs(1);
    return 0;
}