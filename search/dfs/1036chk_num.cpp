#include <bits/stdc++.h>
using namespace std;

vector<int> chosen;
int n, m, ans, arr[20];
void dfs(int x)
{
    if (chosen.size() > m || chosen.size() + (n - x) < m)
        return;
    if (x == n)
    {
        int cnt = 0;
        for (auto i : chosen)
            cnt += i;
        for (int i = 2, up = sqrt(cnt); i <= up; i++)
            if (!(cnt % i))
                return;
        ans += 1;
        return;
    }
    dfs(x + 1);
    chosen.push_back(arr[x]), dfs(x + 1);
    chosen.pop_back();
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    dfs(0);
    cout << ans;
    return 0;
}