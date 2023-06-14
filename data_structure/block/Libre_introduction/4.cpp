#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10, K = 230;
int len, num, pos[N], st[K], ed[K];
long long arr[N], sum[K], tag[K];

void change(int l, int r, int v)
{
    int sid = pos[l], eid = pos[r];
    for (int i = l, up = min(ed[sid], r); i <= up; i++)
        arr[i] += v;
    sum[sid] += (min(ed[sid], r) - l + 1) * v;

    if (sid != eid)
    {
        for (int i = st[eid]; i <= r; i++)
            arr[i] += v;
        sum[eid] += (r - st[eid] + 1) * v;
    }

    for (int i = sid + 1; i <= eid - 1; i++)
        tag[i] += v, sum[i] += len * v;
}
long long query(int l, int r, int p)
{
    int sid = pos[l], eid = pos[r];
    long long res = 0;

    for (int i = l, up = min(ed[sid], r); i <= up; i++)
        (res += arr[i] + tag[sid]) %= p;

    if (sid != eid)
        for (int i = st[eid]; i <= r; i++)
            (res += arr[i] + tag[eid]) %= p;

    for (int i = sid + 1; i <= eid - 1; i++)
        (res += sum[i]) %= p;
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    len = sqrt(n), num = n / len + bool(n % len);
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1,
        ed[i] = i * len;
    ed[num] = n; // the last block in special situation
    for (int i = 1; i <= n; i++)
        pos[i] = (i - 1) / len + 1,
        cin >> arr[i], sum[pos[i]] += arr[i];

    for (int op, l, r, c; n--;)
    {
        cin >> op >> l >> r >> c;
        if (!op)
            change(l, r, c);
        else
            cout << query(l, r, c + 1) << '\n';
    }
    return 0;
}