#include <bits/stdc++.h>
using namespace std;

int pri[15] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
ssize_t best = -1, num = -1;
int n;

void dfs(ssize_t x, int rest, int m, int up)
{
    if (m > best || (m == best && x < num))
        num = x, best = m;
    ssize_t ans = x;
    int i = 0;
    while (i < up)
    {
        ++i;
        if (n / ans < pri[rest])
            return;
        int d = m * (i + 1);
        ans *= pri[rest];
        if (ans <= n)
            dfs(ans, rest + 1, d, i);
    }
}

int main()
{
    cin >> n;
    dfs(1, 1, 1, 30);
    cout << num;
    return 0;
}
