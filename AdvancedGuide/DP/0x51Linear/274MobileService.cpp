/* 这题的状态和转移非常好想：记录三个服务员的位置 (x,y,z)
   然后分阶段分别让这三个服务员去服务第 i + 1 个请求，代价取最小值。
   问题是：这个状态储存和转移的量非常大，细想之后可以发现：服务完第 qi 个请求后，
   一定有且仅有一个服务员在第 qi 个请求的位置，所以我们记录三个人其实是多余了，这不是一个好的状态简化。
   故我们只需记录两个人的位置，剩下那一个人可以推导得出，就像线性代数的线性无关组，减少了多余的状态和转移。
 */
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

constexpr int N = 1005, L = 205;
int f[N][L][L], c[L][L], q[N];
inline void ckmin(int &x, int y) { (y < x) && (x = y); }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#undef endl
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int l, n;
    cin >> l >> n;
    for (int i = 1; i <= l; i++)
        for (int j = 1; j <= l; j++)
            cin >> c[i][j];
    for (int i = 1; i <= n; i++)
        cin >> q[i];
    q[0] = 1;

    memset(f, 0x3f, sizeof f);
    f[0][2][3] = 0;
    for (int i = 0; i < n; i++)
        for (int y = 1; y <= l; y++)
            for (int z = 1; z <= l; z++)
            {
                int x = q[i], p = q[i + 1];
                if (y != p && z != p)
                    ckmin(f[i + 1][y][z], f[i][y][z] + c[x][p]);
                if (x != p && z != p)
                    ckmin(f[i + 1][x][z], f[i][y][z] + c[y][p]);
                if (x != p && y != p)
                    ckmin(f[i + 1][x][y], f[i][y][z] + c[z][p]);
            }
    int res = 0x3f3f3f3f;
    for (int y = 1; y <= l; y++)
        for (int z = 1; z <= l; z++)
            ckmin(res, f[n][y][z]);
    cout << res;
    return 0;
}