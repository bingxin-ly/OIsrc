#include <bits/stdc++.h>
using namespace std;

int f[100010], MOD = 100003;
int main()
{
    int n, k;
    cin >> n >> k;
    f[0] = f[1] = 1;
    /* for (int i = 2; i <= n; i++)
        for (int j = 1; j <= k; j++)
            if (i >= j)
                f[i] += f[i - j], f[i] %= MOD; */

    for (int i = 2; i <= n; i++)
        if (i <= k)
            f[i] = f[i - 1] * 2 % MOD;
        else
            f[i] = (f[i - 1] * 2 - f[i - k - 1]) % MOD;
    cout << (f[n] + MOD) % MOD;
    return 0;
}