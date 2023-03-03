#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10;
int n, c, pos[MAX];

bool check(int x)
{
    int sum = 0, before = pos[1];
    for (int i = 2; i <= n; i++)
    {
        if (pos[i] - before >= x)
            sum++, before = pos[i];
        if (sum >= c)
            return true;
    }
    if (sum + 1 < c)
        return false;
    return true;
}
int main()
{
    cin >> n >> c;
    for (int i = 1; i <= n; i++)
        cin >> pos[i];
    sort(pos + 1, pos + n + 1);

    int l = INT_MAX, r = pos[n] - pos[1];
    for (int i = 2; i <= n; i++)
        l = min(pos[i] - pos[i - 1], l);
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    cout << r << endl;
    return 0;
}