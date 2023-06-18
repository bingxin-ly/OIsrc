#include <bits/stdc++.h>
using namespace std;

const int N = 2e4 + 10, K = 150;
int pos[N], st[K], ed[K], bit[N];
int n, ans;
pair<int, int> arr[N];

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

int query(int l, int r, int v)
{
    int sid = pos[l], eid = pos[r], res = 0;
    for (int i = st[sid]; i <= ed[sid]; i++)
        if (l <= i && i <= r)
            res += arr[i].first < v;
    if (sid != eid)
        for (int i = st[eid]; i <= ed[eid]; i++)
            if (l <= i && i <= r)
                res += arr[i].first < v;
    for (int i = sid + 1; i <= eid - 1; i++)
        res += lower_bound(arr + st[i], arr + ed[i] + 1, v) - (arr + st[i]);
    return res;
}
void exchange(int l, int r)
{
    int sid = pos[l], eid = pos[r], *ln, *rn;
    if (sid == eid)
    {
        for (int i = st[sid]; i <= ed[sid]; i++)
            if (arr[i].second == l)
                ln = &arr[i].first;
            else if (arr[i].second == r)
                rn = &arr[i].first;
        swap(*ln, *rn);
        sort(arr + st[sid], arr + ed[sid] + 1);
        return;
    }

    for (int i = sid)
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    int len = sqrt(n), num = (n - 1) / n + 1;

    for (int i = 1; i <= n; i++)
        cin >> arr[i].first;
    vector<int> val(arr + 1, arr + n + 1);
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 1; i <= n; i++)
        arr[i].first = lower_bound(val.begin(), val.end(), arr[i].first) - val.begin() + 1,
        arr[i].second = i;

    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1, ed[i] = i * len,
        sort(arr + st[i], arr + ed[i] + 1);

    for (int i = 1; i <= n; i++)
        add(arr[i].first), ans += i - ask(arr[i].first);

    int m;
    cin >> m;
    for (int l, r; m--;)
    {
        cin >> l >> r;
        ans += (query(l + 1, r - 1, arr[r].first) - query(l + 1, r - 1, arr[l].first)) << 1;
        ans += arr[l].first < arr[r].first ? 1 : -1;
        cout << ans << '\n';
        exchange(l, r);
    }
    return 0;
}