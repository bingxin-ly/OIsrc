#include <bits/stdc++.h>
using namespace std;

const int N = 2e7 + 10;
int a[N];
int pre[N], suf[N];
signed main()
{
    int n, k, P;
    cin >> n >> k >> P;

    int A, B, C, D;
    cin >> A >> B >> C >> D;
    a[1] = A;
    for (int i = 2; i <= n; i++)
        a[i] = (1ll * a[i - 1] * B + C) % D;

    for (int i = 1; i <= n; i++)
        if (!((i - 1) % k))
            pre[i] = a[i];
        else
            pre[i] = 1ll * pre[i - 1] * a[i] % P;

    suf[n + 1] = 1;
    for (int i = n; i >= 1; i--)
        if (!(i % k))
            suf[i] = a[i];
        else
            suf[i] = 1ll * suf[i + 1] * a[i] % P;

    int ans = 0;
    for (int i = 1; i <= n - k + 1; i++)
        if (!((i - 1) % k))
            ans ^= suf[i];
        else
            ans ^= 1ll * suf[i] * pre[i + k - 1] % P;
    cout << ans;
    return 0;
}