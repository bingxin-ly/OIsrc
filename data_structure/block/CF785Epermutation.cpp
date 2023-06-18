#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, K = 450;
int len, pos[N], arr[N];
vector<int> blo[K];
#define lower(i, x) lower_bound(blo[i].begin(), blo[i].end(), x)
#define upper(i, x) upper_bound(blo[i].begin(), blo[i].end(), x)

void change(int l, int r)
{
    if (pos[l] != pos[r])
    {
        blo[pos[l]].erase(lower(pos[l], arr[l])),
            blo[pos[l]].insert(upper(pos[l], arr[r]), arr[r]);
        blo[pos[r]].erase(lower(pos[r], arr[r])),
            blo[pos[r]].insert(upper(pos[r], arr[l]), arr[l]);
    }
    swap(arr[l], arr[r]);
}
int query(int l, int r, int v)
{
    if (l > r)
        return 0;
    int res = 0;
    for (int i = l, up = min(len * pos[l], r); i <= up; i++)
        res += arr[i] < v;
    if (pos[l] != pos[r])
        for (int i = len * (pos[r] - 1) + 1; i <= r; i++)
            res += arr[i] < v;
    for (int i = pos[l] + 1; i <= pos[r] - 1; i++)
        res += lower(i, v) - blo[i].begin();
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    len = sqrt(n);
    for (int i = 1; i <= n; i++)
        arr[i] = i, pos[i] = (i - 1) / len + 1,
        blo[pos[i]].emplace_back(i);

    long long ans = 0;
    for (int l, r; m--;)
    {
        cin >> l >> r;
        if (l == r)
            cout << ans << '\n';
        else
        {
            if (l > r)
                swap(l, r);
            ans += (query(l + 1, r - 1, arr[r]) - query(l + 1, r - 1, arr[l])) << 1;
            ans += arr[l] < arr[r] ? 1 : -1;
            cout << ans << '\n';
            change(l, r);
        }
    }
    return 0;
}