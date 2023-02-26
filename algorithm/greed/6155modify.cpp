#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 10;
int src[MAX], cost[MAX], diff[MAX];
vector<int> v;
unordered_map<int, int> m;

int fnd(int x)
{
    if (m[x] == 0)
        return m[x] = x + 1;
    return m[x] = fnd(m[x]);
}
bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> src[i];
    sort(src + 1, src + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        int pos = fnd(src[i]) - src[i] - 1;
        if (pos)
            v.push_back(pos);
    }
    for (int i = 1; i <= n; i++)
        cin >> cost[i];
    sort(cost + 1, cost + n + 1);
    sort(v.begin(), v.end());
    size_t ans = 0;
    for (int i = v.size() - 1, j = 1; i >= 0; i--, j++)
        ans += 1ll * v[i] * cost[j];
    cout << ans << endl;
    return 0;
}
