#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, L = 1300, S = 80;
int n, m;
int len, num, pos[N], st[S], ed[S], tag[S];
int sl, san[L << 1];
struct pii
{
    int x, y;
    inline bool operator<(const pii &o) const { return x < o.x; }
    inline bool operator<(int o) const { return x < o; }
} arr[N], inner[L], outer[L];

void pick(int as, int ae, int bs, int be, int l, int r)
{
    int i = as, j = bs, k = 0;
    while (i <= ae && j <= be)
    {
        while (i <= ae && arr[i].y < l)
            ++i;
        while (j <= be && r < arr[j].y)
            ++j;
        if (i > ae || j > be)
            break;
        if (arr[j].x < arr[i].x)
            san[k++] = arr[j++].x;
        else
            san[k++] = arr[i++].x;
    }
    while (i <= ae)
    {
        while (i <= ae && arr[i].y < l)
            ++i;
        if (i > ae)
            break;
        san[k++] = arr[i++].x;
    }
    while (j <= be)
    {
        while (j <= be && r < arr[j].y)
            ++j;
        if (j > be)
            break;
        san[k++] = arr[j++].x;
    }
    sl = k - 1;
}
void extract(int s, int e, int l, int r)
{
    int i = s, j = 0;
    while (i <= e)
    {
        while (i <= e && (arr[i].y < l || r < arr[i].y))
            ++i;
        if (i > e)
            break;
        san[j++] = arr[i++].x;
    }
    sl = j - 1;
}
int seak(int a, int b, int v)
{
    int cnt = lower_bound(san, san + sl + 1, v) - san;
    for (int i = a; i <= b; i++)
        cnt += lower_bound(arr + st[i], arr + ed[i] + 1, v - tag[i]) - (arr + st[i]);
    return cnt + 1;
}
int query(int l, int r, int k)
{
    int fr = pos[l], to = pos[r];
    if (tag[fr])
    {
        for (int i = st[fr]; i <= ed[fr]; i++)
            arr[i].x += tag[fr];
        tag[fr] = 0;
    }
    if (fr != to)
    {
        if (tag[to])
        {
            for (int i = st[to]; i <= ed[to]; i++)
                arr[i].x += tag[to];
            tag[to] = 0;
        }
        pick(st[fr], ed[fr], st[to], ed[to], l, r);
    }
    else
        extract(st[fr], ed[fr], l, r);
    long long L = -2e9, R = 2e9;
    while (L < R)
    {
        int mid = (L + R + 1) >> 1;
        if (seak(fr + 1, to - 1, mid) <= k)
            L = mid;
        else
            R = mid - 1;
    }
    return L;
}
void update(int l, int r, int k)
{
    int fr = pos[l], to = pos[r];
    int in = 0, out = 0;
    for (int i = st[fr]; i <= ed[fr]; i++)
        if (l <= arr[i].y && arr[i].y <= r)
            inner[in].x = arr[i].x + k, inner[in++].y = arr[i].y;
        else
            outer[out++] = arr[i];
    merge(inner, inner + in, outer, outer + out, arr + st[fr]);
    if (fr != to)
    {
        in = 0, out = 0;
        for (int i = st[to]; i <= ed[to]; i++)
            if (arr[i].y <= r)
                inner[in].x = arr[i].x + k, inner[in++].y = arr[i].y;
            else
                outer[out++] = arr[i];
        merge(inner, inner + in, outer, outer + out, arr + st[to]);
    }
    for (int i = fr + 1; i <= to - 1; i++)
        tag[i] += k;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\OIsrc\\.in", "r", stdin);
    freopen("C:\\OIsrc\\.out", "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    len = max(sqrt(n * log2(n)), 1.0), num = (n - 1) / len + 1;
    for (int i = 1; i <= n; i++)
        cin >> arr[i].x, arr[i].y = i, pos[i] = (i - 1) / len + 1;
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1, ed[i] = i * len;
    ed[num] = n;
    for (int i = 1; i <= num; i++)
        sort(arr + st[i], arr + ed[i] + 1);
    for (int op, l, r, k; m--;)
    {
        cin >> op >> l >> r >> k;
        if (op == 1)
            cout << (k <= (r - l + 1) ? query(l, r, k) : -1) << '\n';
        else
            update(l, r, k);
    }
    return 0;
}