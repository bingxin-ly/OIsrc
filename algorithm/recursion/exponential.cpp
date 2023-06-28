#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> v;
void dfs(int x)
{
    if (x == n + 1)
    {
        for (auto i : v)
            cout << i << ' ';
        cout << endl;
        return;
    }
    v.emplace_back(x), dfs(x + 1), v.pop_back();
    dfs(x + 1);
}

signed main()
{
    cin >> n;
    dfs(1);
    return 0;
}