#include <bits/stdc++.h>
using namespace std;

int a[1010];
signed main()
{
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    iota(a + 1, a + n + 1, 1);
    reverse(a + 1, a + n + 1);
    for (int i = 1; i <= k; i++)
        next_permutation(a + 1, a + n + 1);

    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    return 0;
}