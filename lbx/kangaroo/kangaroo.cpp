#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205;
int n, s, t, v[N], ans;

// 0 == left 1 == right
bool check()
{
    for (int i = 1; i <= n; i++)
        if (!v[i] && i != t)
            return 0;
    return 1;
}
void jump(int i, bool dir)
{
    if (!dir)
    {
        for (int j = i + 1; j <= n; j++)
            if (!v[j] && j != t)
                v[j] = 1, jump(j, 1), v[j] = 0;
    }
    else
    {
        for (int j = i - 1; j >= 1; j--)
            if (!v[j] && j != t)
                v[j] = 1, jump(j, 0), v[j] = 0;
    }
    ans += check();
}
signed main()
{
    freopen("kangaroo.in", "r", stdin);
    freopen("kangaroo.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> s >> t;
    v[s] = 1, jump(s, 0), jump(s, 1);
    cout << ans;
    return 0;
}