#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10, K = 1e3 + 10;
int pos[N], st[K], ed[K], tag[K];
pair<int, int> arr[N];

bool ismodi;
int force(int l, int r, int v)
{
    int id = pos[l], res = 0;
    if (ismodi)
    {
        for (int i = st[id]; i <= ed[id]; i++) // 枚举整块！
            if (l <= arr[i].second && arr[i].second <= r)
                arr[i].first += v;
        sort(arr + st[id], arr + ed[id] + 1);
    }
    else
    {
        for (int i = st[id]; i <= ed[id]; i++) // 枚举整块！
            if (l <= arr[i].second && arr[i].second <= r)
                res += arr[i].first >= v;
    }
    return res;
}
void modify(int l, int r, int v)
{
    ismodi = true;
    int sid = pos[l], eid = pos[r];
    force(l, min(r, ed[sid]), v);
    if (sid != eid)
        force(st[eid], r, v);
    for (int i = sid + 1; i <= eid - 1; i++)
        tag[i] += v;
}
int query(int l, int r, int v)
{
    ismodi = false;
    int sid = pos[l], eid = pos[r], res = 0;
    res += force(l, min(r, ed[sid]), v - tag[sid]);
    if (sid != eid)
        res += force(st[eid], r, v - tag[eid]);
    for (int i = sid + 1; i <= eid - 1; i++)
        res += arr + ed[i] + 1 -
               lower_bound(arr + st[i], arr + ed[i] + 1, make_pair(v - tag[i], 0));
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int len = sqrt(n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1, ed[i] = i * len;
    ed[num] = n;

    for (int i = 1; i <= n; i++)
        pos[i] = (i - 1) / len + 1, cin >> arr[i].first, arr[i].second = i;
    for (int i = 1; i <= num; i++)
        sort(arr + st[i], arr + ed[i] + 1);

    char op;
    for (int l, r, x; m--;)
    {
        cin >> op >> l >> r >> x;
        if (op == 'M')
            modify(l, r, x);
        else
            cout << query(l, r, x) << '\n';
    }
    return 0;
}