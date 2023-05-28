#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int sum[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> sum[i], sum[i] += sum[i - 1];
    int ans = 0;
    for (int i = 2; i <= n; i++)
        if (sum[i] > 0)
            ans += sum[i];
    cout << ans;
    return 0;
}