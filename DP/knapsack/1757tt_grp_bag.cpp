#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> intpair;
const int N = 1010;

int n, m;
int v[N][N], w[N][N], s[N];
vector<intpair> grps[N];
int f[N];

int main()
{
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        grps[c].push_back({a, b});
    }

    for (int i = 1; !grps[i].empty(); i++)
    {
        s[i] = grps[i].size();
        for (int j = 0; j < s[i]; j++)
            v[i][j] = grps[i][j].first, w[i][j] = grps[i][j].second;
    }

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 0; k < s[i]; k++)
                if (v[i][k] <= j)
                    f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
    cout << f[m] << endl;
    return 0;
}
