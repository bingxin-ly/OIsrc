#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 10, K = 1e6 + 10;
int n, q;
int a[N], cnt[2 * K];
long long s[N][N];

int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], a[i] += K;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            if (j > i + 1)
                if (a[i] + a[j] <= K * 3 && a[i] + a[j] >= K)
                    s[i][j] = cnt[K * 3 - a[i] - a[j]];
            cnt[a[j]]++;
        }
        for (int j = i + 1; j <= n; ++j)
            cnt[a[j]]--;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    int l, r;
    while (q--)
    {
        cin >> l >> r;
        cout << s[r][r] - s[l - 1][r] - s[r][l - 1] + s[l - 1][l - 1] << endl;
    }

    return 0;
}
