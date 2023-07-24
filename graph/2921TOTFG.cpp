#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, nxt[N], etr[N], dfn[N], col[N], len[N];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> nxt[i];
    for (int i = 1; i <= n; i++)
    {
        int tim = 0;
        for (int j = i;; j = nxt[j], tim++)
        {
            if (!col[j])
                col[j] = i, dfn[j] = tim;
            else if (col[j] == i)
            {
                len[i] = tim - dfn[j], etr[i] = dfn[j];
                cout << tim << '\n';
                break;
            }
            else
            {
                len[i] = len[col[j]];
                etr[i] = tim + max(etr[col[j]] - dfn[j], 0);
                cout << etr[i] + len[i] << '\n';
                break;
            }
        }
    }
    return 0;
}