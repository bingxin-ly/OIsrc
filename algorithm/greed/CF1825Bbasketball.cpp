#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, d, power[N], ans, last;

bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    // freopen("basketball.in", "r", stdin);
    // freopen("basketball.out", "w", stdout);
    cin >> n >> d;
    last = n;
    for (int i = 1; i <= n; i++)
        cin >> power[i];
    sort(power + 1, power + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        int need = 1;
        while (need * power[i] <= d)
            need++;
        last -= need;
        if (last < 0)
            break;
        ans++;
    }
    cout << ans << endl;
    return 0;
}