#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e3 + 10, MOD = 1e8;
int N, F, cows[MAX], f[MAX][MAX];

int main()
{
    cin >> N >> F;
    for (int i = 1; i <= N; i++)
        cin >> cows[i], cows[i] %= F;
    for (int i = 1; i <= N; i++)
        f[i][cows[i]] = 1;
    for (int i = 1; i <= N; i++)
        for (int j = 0; j <= F - 1; j++)
            f[i][j] = ((f[i][j] + f[i - 1][j]) % MOD +
                       f[i - 1][(j - cows[i] + F) % F]) %
                      MOD;
    cout << f[N][0] << endl;
    return 0;
}