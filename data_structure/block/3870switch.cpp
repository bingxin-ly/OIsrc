#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, K = 320;
int len, pos[N], st[K], ed[K], sum[K];
bool arr[N], tag[K];

bool isask;
int force(int l, int r)
{
    int id = pos[l], res = 0;
    if (tag[id])
    {
        for (int i = st[id]; i <= ed[id]; i++)
            arr[i] ^= 1;
        tag[id] = false;
    }
    if (isask)
        for (int i = l; i <= r; i++)
            res += arr[i];
    else
        for (int i = l; i <= r; i++)
            sum[id] += arr[i] ? -1 : 1, arr[i] ^= 1;
    return res;
}
void change(int l, int r)
{
    isask = false;
    int sid = pos[l], eid = pos[r];
    force(l, min(ed[sid], r));
    if (sid != eid)
        force(st[eid], r);
    for (int i = sid + 1; i <= eid - 1; i++)
        tag[i] ^= 1, sum[i] = len - sum[i];
}
int query(int l, int r)
{
    isask = true;
    int sid = pos[l], eid = pos[r], res = 0;
    res += force(l, min(ed[sid], r));
    if (sid != eid)
        res += force(st[eid], r);
    for (int i = sid + 1; i <= eid - 1; i++)
        res += sum[i];
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, num;
    cin >> n >> m;
    len = sqrt(n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1, ed[i] = i * len;
    ed[num] = n;

    for (int i = 1; i <= n; i++)
        pos[i] = (i - 1) / len + 1;

    for (int c, a, b; m--;)
    {
        cin >> c >> a >> b;
        if (!c)
            change(a, b);
        else
            cout << query(a, b) << '\n';
    }
    return 0;
}