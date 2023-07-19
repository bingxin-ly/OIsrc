#include <bits/stdc++.h>
using namespace std;

constexpr int N = 30;
int n, m, in[N], tin[N];
vector<int> g[N];

set<int> num;
vector<int> seq;
int topo()
{
    seq.clear(), memcpy(tin + 1, in + 1, n * sizeof(int));
    queue<int> q;
    for (int i : num)
        if (!tin[i])
            q.emplace(i);
    bool mark = false;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), seq.emplace_back(u);
        bool flag = false;
        for (int v : g[u])
            if (!--tin[v])
                mark |= flag, q.emplace(v), flag = true;
    }
    if (seq.size() < num.size())
        return -1;
    else if (seq.size() == (size_t)n && !mark)
        return 1;
    else
        return 0;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    char str[5];
    for (int i = 1, u, v; i <= m; i++)
    {
        cin >> (str + 1), u = str[1] - 'A' + 1, v = str[3] - 'A' + 1;
        if (u == v)
            return cout << "Inconsistency found after " << i << " relations.", 0;
        num.insert(u), num.insert(v), g[u].emplace_back(v), in[v]++;

        int res = topo();
        if (res == -1)
        {
            cout << "Inconsistency found after " << i << " relations.";
            return 0;
        }
        else if (res == 1)
        {
            cout << "Sorted sequence determined after " << i << " relations: ";
            for (int i : seq)
                cout << char('A' + i - 1);
            cout << ".";
            return 0;
        }
    }
    cout << "Sorted sequence cannot be determined.";
    return 0;
}