#include <bits/stdc++.h>
using namespace std;

int n, d, k;
long long f[500010], nodes[500010][2];

bool check(int g)
{
    int lpos = d - g, rpos = d + g;
    if (lpos <= 0)
        lpos = 1;
    memset(f, ~0x7f, sizeof(f));
    f[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (nodes[i][0] - nodes[j][0] < lpos)
                continue;
            if (nodes[i][0] - nodes[j][0] > rpos)
                break;
            f[i] = max(f[i], f[j] + nodes[i][1]);
            if (f[i] >= k)
                return 1;
        }
    }
    return 0;
}
int main()
{
    cin >> n >> d >> k;
    for (int i = 1; i <= n; i++)
        cin >> nodes[i][0] >> nodes[i][1];
    int l = 0, r = 10005, m = (l + r) / 2;
    int ans;
    while (l <= r)
    {
        if (check(m))
            ans = m, r = m - 1;
        else
            l = m + 1;
        m = (l + r) / 2;
    }
    cout << ans;
    return 0;
}
