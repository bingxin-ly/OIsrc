#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
bool vis[N][N];
int h[N];

// 先把所有牛的高度假设为最高值，如果某两头牛之间能互相看到的话
// 那直接把中间所有牛都砍一刀（中间这些牛的高度都减一）
// 只是实现上有差异
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, r;
    cin >> n >> h[0] >> h[0] >> r;
    /* for (int i = 1; i <= n; i++)
        h[i] = hmx; */
    for (int a, b; r--;)
    {
        cin >> a >> b;
        if (a > b)
            swap(a, b);
        if (vis[a][b])
            continue;
        vis[a][b] = true;
        /* for (int j = a + 1; j < b; j++)
            h[j]--; */
        h[a + 1]--, h[b]++;
    }
    for (int i = 1; i <= n; i++)
        cout << (/* h[i] */ h[i] += h[i - 1]) << '\n';
    return 0;
}