#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int N = 5e4 + 10; // sqrt(5e4) ~ 223.6
int len, num, pos[N], st[225], ed[225], tag[225];
pii arr[N];

int force(int l, int r, int d, bool type)
{
    int id = pos[l], res = 0;
    // std::copy, std::move is the C++ way.
    // vector::date() returns a typical(C-like) pointer.
    // memcpy is the C (and the old, obsolete and stinky "traditional C++") way.
    // for is the fools' way. DO NOT DO THIS.
    if (type)
    {
        for (int i = st[id]; i <= ed[id]; i++)
            if (l <= arr[i].second && arr[i].second <= r)
                arr[i].first += d;
        sort(arr + st[id], arr + ed[id] + 1);
    }
    else
        for (int i = st[id]; i <= ed[id]; i++)
            if (l <= arr[i].second && arr[i].second <= r)
                res += arr[i].first < d;
    return res;
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
    int sid = pos[l], eid = pos[r], res = 0;
    if (sid == eid)
        return force(l, r, c - tag[sid], false);

    res += force(l, ed[sid], c - tag[sid], false);
    for (int i = sid + 1; i <= eid - 1; i++)
        res += lower_bound(arr + st[i], arr + ed[i] + 1, make_pair(c - tag[i], 0)) - (arr + st[i]);
    res += force(st[eid], r, c - tag[eid], false);
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
            cout << query(l, r, c * c) << '\n';
    }
    return 0;
}