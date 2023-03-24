#include <bits/stdc++.h>
#define A(i) mp[a[i]]
#define B(i) mp[b[i]]
#define C(i) mp[c[i]]
using namespace std;

const int N = 30;
/* 不断枚举 map中的排列，加之以取舍
   a, b, c三个原数组, 其中的数字按照 mp进行映射 */
int n, mp[N], vis[N];
char a[N], b[N], c[N], p[N];
// (A[i] + B[i]) mod n != C[i]
// 和 (A[i] + B[i] + 1) mod n != C[i]
bool judge()
{
    for (int i = n - 1; i >= 0; i--)
    {
        // if (A(i) == -1 || B(i) == -1 || C(i) == -1)
        //     return false;
        if ((A(i) + B(i)) % n != C(i) &&
            (A(i) + B(i) + 1) % n != C(i))
            return false;
    }
    return true;
}
void dfs(int now)
{
    if (now == n)
    {
        int up = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            int s = A(i) + B(i) + up;
            if (C(i) != s % n)
                return;
            up = s / n;
        }
        for (int i = 0; i < n; i++)
            cout << mp[i] << ' ';
        exit(0);
    }
    if (A(0) + B(0) >= n)
        return;
    for (int i = n - 1; i >= 0; i--)
    {
        int A = A(i), B = B(i), C = C(i);
        if (A == -1 || B == -1 || C == -1)
            continue;
        if ((A + B) % n != C && (A + B + 1) % n != C)
            return;
    }

    for (int i = n - 1; i >= 0; i--)
        if (!vis[i])
        {
            mp[p[now]] = i;
            vis[i] = true;
            // mp[now] = i;
            dfs(now + 1);
            mp[p[now]] = -1;
            vis[i] = false;
        }
}
int cnt;
void put(int x)
{
    if (!vis[x])
    {
        vis[x] = true;
        p[cnt++] = x;
    }
}

int main()
{
    memset(mp, -1, sizeof(mp));
    cin >> n;

    cin >> a;
    for (int i = 0; i < n; i++)
        a[i] -= 'A';
    cin >> b;
    for (int i = 0; i < n; i++)
        b[i] -= 'A';
    cin >> c;
    for (int i = 0; i < n; i++)
        c[i] -= 'A';

    for (int i = n - 1; i >= 0; i--)
        put(a[i]), put(b[i]), put(c[i]);

    memset(vis, false, sizeof(vis));
    dfs(0);

    return 0;
}
