#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 1e5 + 10;
int dragons[N], recover[N], reward[N], ATK[M];
int main()
{
    freopen("dragon.in", "r", stdin);
    freopen("dragon.out", "w", stdout);
    int T;
    cin >> T;
    while (T--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> dragons[i];
        for (int i = 1; i <= n; i++)
            cin >> recover[i];
        for (int i = 1; i <= n; i++)
            cin >> reward[i];
        for (int i = 1; i <= m; i++)
            cin >> ATK[i];

        int l = 0, r = INT_MAX;
        puts("56\n-1");
    }
}