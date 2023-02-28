#include <bits/stdc++.h>
using namespace std;

int d, n, m;
int lens[50010];
int ans;

bool check(int x)
{
    int cnt = 0, now = 0;
    for (int i = 1; i <= n + 1; i++)
    {
        if (lens[i] - lens[now] < x)
            cnt++;
        else
            now = i;
    }
    if (cnt > m)
        return 0;
    return 1;
}

int main()
{
    cin >> d >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> lens[i];
    lens[n + 1] = d;
    int l = 1, r = d, mid;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (check(mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    cout << ans << endl;
}