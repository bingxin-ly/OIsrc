#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
vector<int> primes(N);
vector<bool> vis(N);
int cnt;
int euler()
{
    for (int i = 2; i <= N; ++i)
    {
        if (!vis[i])
            primes[cnt++] = i;
        for (int j = 0; j < cnt; ++j)
        {
            if (1ll * i * primes[j] > N)
                break;
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0)
                break;
        }
    }
    return cnt;
}

int main()
{
    size_t l, r;
    cin >> l >> r;
    if (l == 1)
        l = 2;
    euler();
    vis.assign(N, false);
    for (int i = 0; i < cnt; i++)
    {
        size_t p = primes[i],
               s = max((l + p - 1) / p * p, 2 * p);
        for (int j = s; j <= r; j += p)
            vis[j - l + 1] = true;
    }
    size_t ans = 0;
    for (int i = 1; i <= r - l + 1; i++)
        if (!vis[i])
            ans++;
    cout << ans;
    return 0;
}