// 不要这么模拟！！从人数角度考虑即可
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, d, power[N], ans, last;
bool used[N];

bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    // freopen("basketball.in", "r", stdin);
    // freopen("basketball.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> d;
    last = n;
    for (int i = 1; i <= n; i++)
        cin >> power[i];
    sort(power + 1, power + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        if (used[i])
            continue;
        used[i] = true;
        int need = 1;
        while (need * power[i] <= d)
            need++;
        // cout << "Now this is " << i << endl;
        // cout << "He need " << need << " persons: " << need * power[i] << endl;

        int cnt = 1;
        for (int k = n; k >= 1; k--)
        {
            if (need == cnt)
                break;
            if (!used[k])
            {
                cnt++;
                used[k] = true;
            }
        }
        if (cnt >= need)
            ans++;
    }
    cout << ans << endl;
    return 0;
}