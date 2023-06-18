#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
char s[N];
signed main()
{
    freopen("bracket.in", "r", stdin);
    freopen("bracket.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m, lst = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> s[i], lst += s[i] == '(' ? +1 : -1;
    lst = abs(lst);
    if (lst + m > n)
        cout << 0, exit(0);
}