#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\.in");
ofstream fout("D:\\OIsrc\\.out");
#define cin fin
#define cout fout
#endif

constexpr int N = 30 * 3 + 5;
struct rect
{
    int x, y, h;
} s[N];
int f[N];
inline void twist(int i) { s[i].x < s[i].y && (swap(s[i].x, s[i].y), true); }

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    s[0] = {INT_MAX, INT_MAX, INT_MAX};
    int n, id = 0;
    while (cin >> n, n)
    {
        memset(f, 0, sizeof f);
        for (int i = 1, x, y, z, b; i <= n; i++)
        {
            cin >> x >> y >> z, b = (i - 1) * 3;
            s[b + 1] = {x, y, z}, twist(b + 1);
            s[b + 2] = {x, z, y}, twist(b + 2);
            s[b + 3] = {y, z, x}, twist(b + 3);
        }
        n = n * 3;
        sort(s + 1, s + n + 1, [](const rect &a, const rect &b)
             { return a.x + a.y > b.x + b.y; });
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                if ((s[i].x < s[j].x && s[i].y < s[j].y) || (s[i].x < s[j].y && s[i].y < s[j].x))
                    f[i] = max(f[i], f[j] + s[i].h);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans = max(ans, f[i]);
        cout << "Case " << ++id << ": maximum height = " << ans << '\n';
    }
    return 0;
}