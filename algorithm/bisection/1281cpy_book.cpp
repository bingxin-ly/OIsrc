#include <bits/stdc++.h>
using namespace std;

int m, k;
int books[510];
int x[510], y[510];

bool check(int mid)
{
    int cnt = 1, now = 0;
    for (int i = m; i >= 1; i--)
    {
        if (now + books[i] > mid)
            now = 0, cnt++;
        now += books[i];
    }
    return cnt <= k;
}

int main()
{
    cin >> m >> k;
    int l = 0, r = 0, mid;
    for (int i = 1; i <= m; i++)
    {
        cin >> books[i];
        r += books[i];
        l = max(l, books[i]);
    }
    while (l < r - 1)
    {
        mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    int cnt = 1, now = 0;
    y[1] = m;
    for (int i = m; i >= 1; i--)
    {
        if (now + books[i] > r)
        {
            now = 0;
            x[cnt] = i + 1;
            y[++cnt] = i;
        }
        now += books[i];
    }
    x[cnt] = 1;
    for (int i = k; i >= 1; i--)
        cout << x[i] << " " << y[i] << endl;
    return 0;
}
