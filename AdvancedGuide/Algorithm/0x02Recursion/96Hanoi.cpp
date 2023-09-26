#include <bits/stdc++.h>
using namespace std;

int d[15], f[15];
signed main() {
    memset(f, 0x3f, sizeof f), d[1] = f[1] = 1;
    for (int i = 2; i <= 12; i++)
        d[i] = 2 * d[i - 1] + 1;
    for (int i = 2; i <= 12; i++)
        for (int j = 1; j < i; j++)
            f[i] = min(f[i], 2 * f[j] + d[i - j]);
    for (int i = 1; i <= 12; i++) cout << f[i] << '\n';
    return 0;
}