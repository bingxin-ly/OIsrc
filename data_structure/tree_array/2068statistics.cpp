#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int n, v[N];
inline int lowbit(int x) { return x & -x; }
void add(int p, int x)
{
    for (; p <= n; p += lowbit(p))
        v[p] += x;
}
int query(int p)
{
    int res = 0;
    for (; p; p -= lowbit(p))
        res += v[p];
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int w;
    cin >> n >> w;
    char opt;
    for (int a, b; w--;)
    {
        cin >> opt >> a >> b;
        if (opt == 'x')
            add(a, b);
        else
            cout << query(b) - query(a - 1) << '\n';
    }
    return 0;
}