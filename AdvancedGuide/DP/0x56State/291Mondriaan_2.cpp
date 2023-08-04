#include <bits/stdc++.h>
using namespace std;

int n, m;
long long f[12][1 << 11];

vector<int> st;
void dfs(int i, int s, int t)
{
    if (i == m)
        return st.emplace_back(t), void();
    if (s >> i & 1)
        dfs(i + 1, s, t);
    else
    {
        dfs(i + 1, s, t | 1 << i);
        if (i < m - 1 && !(s >> (i + 1) & 1))
            dfs(i + 2, s, t);
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    while (cin >> n >> m, n || m)
    {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 1 << m; j++)
                if (f[i][j] > 0)
                {
                    st.clear(), dfs(j, 0, 0);
                    for (int k : st)
                        f[i + 1][k] += f[i][j];
                }
        cout << f[n][0] << '\n';
    }
    return 0;
}