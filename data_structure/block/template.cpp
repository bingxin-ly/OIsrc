#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10, K = 230;
int pos[N], len;
long long arr[N], tag[230], sum[230];

void add(int l, int r, long long x)
{
    int st = pos[l], ed = pos[r];
    if (st == ed)
    {
        for (int i = l; i <= r; i++)
            arr[i] += x, sum[st] += x;
        return;
    }

    for (int i = l; pos[i] == st; i++)
        arr[i] += x, sum[st] += x;
    for (int i = st + 1; i <= ed - 1; i++)
        tag[i] += x, sum[i] += len * x;
    for (int i = r; pos[i] == ed; i--)
        arr[i] += x, sum[ed] += x;
}

long long query(int l, int r, long long p)
{
    int st = pos[l], ed = pos[r];
    long long ans = 0;
    if (st == ed)
    {
        for (int i = l; i <= r; i++)
            (ans += arr[i] + tag[st]) %= p;
        return ans;
    }

    for (int i = l; pos[i] == st; i++)
        (ans += arr[i] + tag[st]) %= p;
    for (int i = st + 1; i <= ed - 1; i++)
        (ans += sum[i]) %= p;
    for (int i = r; pos[i] == ed; i--)
        (ans += arr[i] + tag[ed]) %= p;
    return ans;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    len = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        pos[i] = (i - 1) / len + 1; // 分块主要体现
        sum[pos[i]] += arr[i];
    }
    for (int i = 1, op, l, r, c; i <= n; i++)
    {
        cin >> op >> l >> r >> c;
        if (!op)
            add(l, r, c);
        else
            cout << query(l, r, c + 1) << '\n';
    }
    return 0;
}