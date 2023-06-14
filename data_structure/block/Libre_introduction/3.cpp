#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10; // sqrt(1e5) ~ 316.2
int len, num, pos[N], st[320], ed[320], tag[320];
pair<int, int> arr[N];

int force(int l, int r, int v, bool type)
{
    int id = pos[l], maxn = -1;
    if (type)
    {
        for (int i = st[id]; i <= ed[id]; i++)
            if (l <= arr[i].second && arr[i].second <= r)
                arr[i].first += v;
        sort(arr + st[id], arr + ed[id] + 1);
    }
    else
        for (int i = st[id]; i <= ed[id]; i++)
            if (l <= arr[i].second && arr[i].second <= r && arr[i].first + tag[id] < v)
                maxn = max(maxn, arr[i].first + tag[id]);
    return maxn;
}
void change(int l, int r, int d)
{
    int sid = pos[l], eid = pos[r];
    if (sid == eid)
        return force(l, r, d, true), void();
    force(l, ed[sid], d, true);
    for (int i = sid + 1; i <= eid - 1; i++)
        tag[i] += d;
    force(st[eid], r, d, true);
}

int query(int l, int r, int c)
{
    int sid = pos[l], eid = pos[r], res = -1;
    if (sid == eid)
        return force(l, r, c, false);

    res = max(res, force(l, ed[sid], c, false));
    for (int i = sid + 1; i <= eid - 1; i++)
    {
        auto p = lower_bound(arr + st[i], arr + ed[i] + 1, make_pair(c - tag[i], 0));
        if (p == arr + st[i])
            continue;
        res = max(res, (--p)->first + tag[i]);
    }
    res = max(res, force(st[eid], r, c, false));
    return res;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    len = sqrt(n), num = n / len + bool(n % len);
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1,
        ed[i] = i * len;
    ed[num] = n;
    for (int i = 1; i <= n; i++)
    {
        pos[i] = (i - 1) / len + 1;
        cin >> arr[i].first, arr[i].second = i;
    }
    for (int i = 1; i <= num; i++)
        sort(arr + st[i], arr + ed[i] + 1);

    for (int op, l, r, c; n--;)
    {
        cin >> op >> l >> r >> c;
        if (!op)
            change(l, r, c);
        else
            cout << query(l, r, c) << '\n';
    }
    return 0;
}