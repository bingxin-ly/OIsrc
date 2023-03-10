#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e2 + 10;
int n, e[MAXN], s[MAXN][MAXN], maxx = -1;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> e[i], e[i + n] = e[i];
    for (int i = 2; i < 2 * n; i++)
        for (int j = i - 1; i - j < n && j >= 1; j--)
        {
            for (int k = j; k < i; k++)
                s[j][i] = max(s[j][i], s[j][k] + s[k + 1][i] + e[j] * e[k + 1] * e[i + 1]);
            maxx = max(s[j][i], maxx);
        }
    cout << maxx;
    return 0;
}