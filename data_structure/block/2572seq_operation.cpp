#include <cmath>
#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
#define endl '\n'
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\.in");
ofstream fout("D:\\OIsrc\\.out");
#define cin fin
#define cout fout
#undef endl
#endif

constexpr int N = 1e5 + 5, K = 320;
int len, arr[N], pos[N], st[K], ed[K];
int lone[K], rone[K], lzro[K], rzro[K];
int one[K], zro[K], sum[K];
int tag[K], flp[K];

inline int max(int x, int y) { return x > y ? x : y; }
void updlc(int id)
{
    for (int i = st[id]; i <= ed[id]; i++)
        if (!arr[i])
            break;
        else
            lone[id] += 1;
    for (int i = st[id]; i <= ed[id]; i++)
        if (arr[i])
            break;
        else
            lzro[id] += 1;
}
void updrc(int id)
{
    for (int i = ed[id]; i >= st[id]; i--)
        if (!arr[i])
            break;
        else
            rone[id] += 1;
    for (int i = ed[id]; i >= st[id]; i--)
        if (arr[i])
            break;
        else
            rzro[id] += 1;
}
void updsum_coi(int id)
{
    for (int i = st[id], cone = 0, czro = 0; i <= ed[id]; i++)
    {
        sum[id] += arr[i];
        if (arr[i])
            one[id] = max(one[id], ++cone), czro = 0;
        else
            zro[id] = max(zro[id], ++czro), cone = 0;
    }
}
void pushup(int id)
{
    lone[id] = lzro[id] = rone[id] = rzro[id] =
        one[id] = zro[id] = sum[id] = 0;
    updlc(id), updrc(id), updsum_coi(id);
}
void pushdown(int id)
{
    assert(!((tag[id] != -1) & flp[id]));
    if (tag[id] != -1)
        fill(arr + st[id], arr + ed[id] + 1, tag[id]);
    if (flp[id])
        for (int i = st[id]; i <= ed[id]; i++)
            arr[i] ^= 1;
    tag[id] = -1, flp[id] = 0;
}

void reset(int l, int r)
{
    int sid = pos[l], eid = pos[r];
    for (int i = sid + 1; i <= eid - 1; i++)
    {
        tag[i] = 0, flp[i] = 0, sum[i] = 0;
        lone[i] = rone[i] = one[i] = 0, lzro[i] = rzro[i] = zro[i] = len;
    }
    {
        pushdown(sid);
        fill(arr + l, arr + min(r, ed[sid]) + 1, 0);
        pushup(sid);
    }
    if (sid != eid)
    {
        pushdown(eid);
        fill(arr + st[eid], arr + r + 1, 0);
        pushup(eid);
    }
}
void set(int l, int r)
{
    int sid = pos[l], eid = pos[r];
    for (int i = sid + 1; i <= eid - 1; i++)
    {
        tag[i] = 1, flp[i] = 0, sum[i] = len;
        lone[i] = rone[i] = one[i] = len, lzro[i] = rzro[i] = zro[i] = 0;
    }
    {
        pushdown(sid);
        fill(arr + l, arr + min(r, ed[sid]) + 1, 1);
        pushup(sid);
    }
    if (sid != eid)
    {
        pushdown(eid);
        fill(arr + st[eid], arr + r + 1, 1);
        pushup(eid);
    }
}
void flip(int l, int r)
{
    int sid = pos[l], eid = pos[r];
    for (int i = sid + 1; i <= eid - 1; i++)
    {
        if (tag[i] != -1)
            tag[i] ^= 1;
        else
            flp[i] ^= 1;
        swap(lone[i], lzro[i]), swap(rone[i], rzro[i]), swap(one[i], zro[i]);
        sum[i] = len - sum[i];
    }
    {
        pushdown(sid);
        for (int i = l, up = min(r, ed[sid]); i <= up; i++)
            arr[i] ^= 1;
        pushup(sid);
    }
    if (sid != eid)
    {
        pushdown(eid);
        for (int i = st[eid]; i <= r; i++)
            arr[i] ^= 1;
        pushup(eid);
    }
}
int count(int l, int r)
{
    int sid = pos[l], eid = pos[r], ret = 0;
    for (int i = sid + 1; i <= eid - 1; i++)
        ret += sum[i];
    {
        pushdown(sid);
        for (int i = l, up = min(r, ed[sid]); i <= up; i++)
            ret += arr[i];
    }
    if (sid != eid)
    {
        pushdown(eid);
        for (int i = st[eid]; i <= r; i++)
            ret += arr[i];
    }
    return ret;
}
int conti(int l, int r)
{
    int sid = pos[l], eid = pos[r], res = 0;
    pushdown(sid);
    int cnt = 0;
    for (int i = l, up = min(r, ed[sid]); i <= up; i++)
        if (!arr[i])
            res = max(res, cnt), cnt = 0;
        else
            cnt += 1;
    res = max(res, cnt);
    if (r <= ed[sid])
        return res;
    int pre = 0;
    for (int i = ed[sid]; i >= l; i--)
        if (!arr[i])
            break;
        else
            pre += 1;

    for (int i = sid + 1; i <= eid - 1; i++)
    {
        res = max(res, pre + lone[i]);
        if (one[i] == len)
            pre += len;
        else
            res = max(res, one[i]), pre = rone[i];
    }

    pushdown(eid);
    for (int i = st[eid]; i <= r; i++)
        if (!arr[i])
            break;
        else
            pre += 1;
    res = max(res, pre);

    cnt = 0;
    for (int i = st[eid]; i <= r; i++)
        if (!arr[i])
            res = max(res, cnt), cnt = 0;
        else
            cnt += 1;
    res = max(res, cnt);
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, num;
    cin >> n >> m;
    len = sqrt(n), num = n / len;
    for (int i = 0; i < n; i++)
        pos[i] = i / len, cin >> arr[i];
    for (int i = 0; i <= num; i++)
        st[i] = i * len, ed[i] = st[i] + len - 1;
    ed[num] = n - 1;

    for (int id = 0; id <= num; id++)
        tag[id] = -1, updlc(id), updrc(id), updsum_coi(id);

    for (int op, l, r; m--;)
    {
        cin >> op >> l >> r;
        switch (op)
        {
        case 0:
            reset(l, r);
            break;
        case 1:
            set(l, r);
            break;
        case 2:
            flip(l, r);
            break;
        case 3:
            cout << count(l, r) << endl;
            break;
        case 4:
            cout << conti(l, r) << endl;
            break;
        }
    }
    return 0;
}