#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int N = 2e4 + 10, K = 150;
int pos[N], st[K], ed[K], bit[N];
int n, ans, ori[N], arr[N];

void add(int p)
{
    for (; p <= n; p += p & -p)
        bit[p] += 1;
}
int ask(int p)
{
    int res = 0;
    for (; p; p -= p & -p)
        res += bit[p];
    return res;
}

int lower(int l, int r, int v)
{
    if (l > r)
        return 0;
    int sid = pos[l], eid = pos[r], res = 0;
    for (int i = l, up = min(r, ed[sid]); i <= up; i++)
        res += ori[i] < v;
    if (sid != eid)
        for (int i = st[eid]; i <= r; i++)
            res += ori[i] < v;
    for (int i = sid + 1; i <= eid - 1; i++)
        res += lower_bound(arr + st[i], arr + ed[i] + 1, v) - (arr + st[i]);
    return res;
}
int upper(int l, int r, int v)
{
    if (l > r)
        return 0;
    int sid = pos[l], eid = pos[r], res = 0;
    for (int i = l, up = min(r, ed[sid]); i <= up; i++)
        res += ori[i] > v;
    if (sid != eid)
        for (int i = st[eid]; i <= r; i++)
            res += ori[i] > v;
    for (int i = sid + 1; i <= eid - 1; i++)
        res += (arr + ed[i] + 1) - upper_bound(arr + st[i], arr + ed[i] + 1, v);
    return res;
}
void exchange(int l, int r)
{
    swap(ori[l], ori[r]);
    int sid = pos[l], eid = pos[r];
    copy(ori + st[sid], ori + ed[sid] + 1, arr + st[sid]),
        sort(arr + st[sid], arr + ed[sid] + 1);

    copy(ori + st[eid], ori + ed[eid] + 1, arr + st[eid]),
        sort(arr + st[eid], arr + ed[eid] + 1);
}

signed main()
{
    n = read();
    int len = sqrt(n), num = (n - 1) / len + 1;

    for (int i = 1; i <= n; i++)
        pos[i] = (i - 1) / len + 1, arr[i] = read();
    vector<int> val(arr + 1, arr + n + 1);
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 1; i <= n; i++)
        ori[i] = arr[i] = lower_bound(val.begin(), val.end(), arr[i]) - val.begin() + 1;

    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1, ed[i] = i * len,
        sort(arr + st[i], arr + ed[i] + 1);

    for (int i = 1; i <= n; i++)
        add(ori[i]), ans += i - ask(ori[i]);
    printf("%d\n", ans);

    int m = read();
    for (int l, r; m--;)
    {
        l = read(), r = read();
        if (l > r)
            swap(l, r);
        // 显然，对于区间 [i+1,j-1] 中
        // 每一个大于 a 的数字会产生 +1 的贡献，每一个小于 a 的数字会产生 -1 的贡献，
        // 每一个小于 b 的数字会产生 +1 的贡献，每一个大于 b 的数字会产生 -1 的贡献。
        // 最后还有 a 与 b 是否为逆序对的贡献。
        ans += upper(l + 1, r - 1, ori[l]) - lower(l + 1, r - 1, ori[l]) +
               lower(l + 1, r - 1, ori[r]) - upper(l + 1, r - 1, ori[r]);
        if (ori[l] != ori[r])
            ans += ori[l] < ori[r] ? 1 : -1, exchange(l, r);
        printf("%d\n", ans);
    }
    return 0;
}