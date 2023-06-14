#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10;
int len, pos[N];
int arr[N], tag[225]; // sqrt(5e4) ~ 223.6

void change(int l, int r, int d)
{
    int sid = pos[l], eid = pos[r];
    if (sid == eid)
    {
        for (int i = l; i <= r; i++)
            arr[i] += d;
        return;
    }
    for (int i = l; pos[i] == sid; i++)
        arr[i] += d;
    for (int i = sid + 1; i <= eid - 1; i++)
        tag[i] += d;
    for (int i = r; pos[i] == eid; i--)
        arr[i] += d;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    len = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        pos[i] = (i - 1) / len + 1;
        cin >> arr[i];
    }
    for (int op, l, r, c; n--;)
    {

        cin >> op >> l >> r >> c;
        if (!op)
            change(l, r, c);
        else
            cout << arr[r] + tag[pos[r]] << '\n';
    }
    return 0;
}