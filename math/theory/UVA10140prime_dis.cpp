#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int cnt, primes[N];
bool vis[N];

inline void chkmin(ssize_t &x, ssize_t a, ssize_t b, ssize_t &p1, ssize_t &p2)
{
    if (x > b - a)
        x = b - a, p1 = a, p2 = b;
}
inline void chkmax(ssize_t &x, ssize_t a, ssize_t b, ssize_t &p1, ssize_t &p2)
{
    if (x < b - a)
        x = b - a, p1 = a, p2 = b;
}
void euler()
{
    for (int i = 2; i < N; ++i)
    {
        if (!vis[i])
            primes[++cnt] = i;
        for (int j = 1; j <= cnt && i * primes[j] < N; ++j)
        {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0)
                break;
        }
    }
}
int main()
{
    ssize_t l, r;
    while (cin >> l >> r)
    {
        l = l == 1 ? 2 : l;
        euler();
        memset(vis, false, sizeof(vis));
        // if (l == 1)
        //     vis[0] = 1;
        for (int i = 1; i <= cnt; ++i)
        {
            for (ssize_t j = l / primes[i]; j * primes[i] <= r; ++j)
            {
                ssize_t x = primes[i] * j;
                if (j > 1 && x >= l)
                    vis[x - l] = true;
            }
        }
        ssize_t prime = 0, p1, p2, p3, p4, mn = 1ll << 60, mx = 0;
        for (ssize_t i = l; i <= r; ++i)
        {
            if (vis[i - l])
                continue;
            if (prime)
                chkmin(mn, prime, i, p1, p2), chkmax(mx, prime, i, p3, p4);
            prime = i;
        }
        if (!mx)
            puts("There are no adjacent primes.");
        else
            printf("%lld,%lld are closest, %lld,%lld are most distant.\n", p1, p2, p3, p4);
    }
    return 0;
}
