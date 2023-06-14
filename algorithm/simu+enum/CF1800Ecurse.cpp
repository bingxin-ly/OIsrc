#include <bits/stdc++.h>
using namespace std;

int vis1[30], vis2[30];
void solve()
{
    static int n, k;
    static string s1, s2;
    cin >> n >> k >> s1 >> s2;
    memset(vis1, 0, sizeof vis1), memset(vis2, 0, sizeof vis2);
    for (int i = 0; i < n; i++)
        vis1[s1[i] - 'a'] += 1, vis2[s2[i] - 'a'] += 1;
    for (int i = 0; i < 26; i++)
        if (vis1[i] != vis2[i])
            return cout << "NO\n", void();

    for (int i = 0; i < n; i++)
        if (i + k >= n && i - k < 0)
            if (s1[i] != s2[i])
                return cout << "NO\n", void();
    cout << "YES\n";
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T;
    for (cin >> T; T--;)
        solve();
    return 0;
}