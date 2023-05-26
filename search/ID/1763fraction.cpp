#include <bits/stdc++.h>
#define int long long
using namespace std;

bool suc;
int lim, ans, num[1010], tot[1010];
void dfs(int dep, int nume, int den, int pre)
{
    if (dep == lim + 1)
    {
        if (!nume)
        {
            suc = true;
            if (num[lim] < tot[lim])
            {
                for (int i = 1; i <= lim; i++)
                    tot[i] = num[i];
                ans = num[lim];
            }
        }
        return;
    }
    if ((den * (lim + 1 - dep)) / nume > ans || num[dep] > ans)
        return;

    for (int i = max(pre, den / nume); i <= den * (lim + 1 - dep) / nume; i++)
    {
        num[dep] = i;
        dfs(dep + 1, nume * i - den, den * i, i + 1);
    }
}

signed main()
{
    int a, b;
    cin >> a >> b;
    while (!suc)
    {
        tot[++lim] = 0x3f3f3f3f, ans = 0x3f3f3f3f;
        dfs(1, a, b, 1);
    }
    for (int i = 1; i <= lim; i++)
        cout << tot[i] << ' ';
    return 0;
}
