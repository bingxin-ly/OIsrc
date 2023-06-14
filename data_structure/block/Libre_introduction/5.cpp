#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10, K = 225; // sqrt(5e4) ~ 223.6
int pos[N], st[K], ed[K];
int arr[N], mxn[K];
long long sum[K];

long long force(int l, int r, bool op)
{
    long long res = 0;

    if (op)
        for (int i = l; i <= r; i++)
            arr[i] = sqrt(arr[i]);
    else
        for (int i = l; i <= r; i++)
            res += arr[i];

    return res;
}
inline void update(int id)
{
    sum[id] = 0, mxn[id] = -1;

    for (int i = st[id]; i <= ed[id]; i++)
        sum[id] += arr[i], mxn[id] = max(mxn[id], arr[i]);
}
void change(int l, int r)
{
    int sid = pos[l], eid = pos[r];

    if (sid == eid)
    {
        if (mxn[sid] > 1)
            force(l, r, true), update(sid);

        return;
    }

    force(l, ed[sid], true), update(sid);

    for (int i = sid + 1; i <= eid - 1; i++)
        if (mxn[i] > 1)
        {
            force(st[i], ed[i], true);
            mxn[i] = sqrt(mxn[i]), sum[i] = 0;

            for (int j = st[i]; j <= ed[i]; j++)
                sum[i] += arr[j];
        }

    force(st[eid], r, true), update(eid);
}
long long query(int l, int r)
{
    int sid = pos[l], eid = pos[r];

    if (sid == eid)
        return force(l, r, false);

    long long res = 0;
    res += force(l, ed[sid], false);

    for (int i = sid + 1; i <= eid - 1; i++)
        res += sum[i];

    res += force(st[eid], r, false);
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    int len = sqrt(n), num = n / len + bool(n % len);

    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1, ed[i] = i * len;

    ed[num] = n;

    for (int i = 1; i <= n; i++)
    {
        pos[i] = (i - 1) / len + 1;
        cin >> arr[i];
        int b = pos[i];
        sum[b] += arr[i], mxn[b] = max(mxn[b], arr[i]);
    }

    for (int op, l, r, c; n--;)
    {
        cin >> op >> l >> r >> c;

        if (!op)
            change(l, r);
        else
            cout << query(l, r) << '\n';
    }

    return 0;
}