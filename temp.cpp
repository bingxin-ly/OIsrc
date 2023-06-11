#include <bits/stdc++.h>
#define long long long
using namespace std;

const int N = 1e5 + 10;
int len, num, st[N], ed[N], pos[N];
int arr[N], sum[N], tag[N];

void change(int l, int r, int d)
{
    int s = pos[l], e = pos[r];
    if (s == e)
    {
        for (int i = l; i <= r; i++)
            arr[i] += d;
        sum[s] += (r - l + 1) * d;
        return;
    }
    for (int i = l; i <= ed[s]; i++)
        arr[i] += d;
    sum[s] += (ed[s] - l + 1) * d;
    for (int i = s + 1; i <= e - 1; i++)
        tag[i] += d, sum[i] += (ed[i] - st[i] + 1) * d;
    for (int i = st[e]; i <= r; i++)
        arr[i] += d;
    sum[e] += (r - st[e] + 1) * d;
}
long query(int l, int r)
{
    int s = pos[l], e = pos[r];
    long res = 0;
    if (s == e)
    {
        for (int i = l; i <= r; i++)
            res += arr[i];
        res += (r - l + 1) * tag[s]; // note! the block may also be added totally before
        return res;
    }
    for (int i = l; i <= ed[s]; i++)
        res += arr[i];
    res += (ed[e] - l + 1) * tag[s];
    for (int i = s + 1; i <= e - 1; i++)
        res += sum[i];
    for (int i = st[e]; i <= r; i++)
        res += arr[i];
    res += (r - st[e] + 1) * tag[e];
    return res;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    len = sqrt(n), num = ceil(1.0 * n / len);
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1,
        ed[i] = i * len;
    ed[num] = n; // the last block in special situation
    for (int i = 1; i <= n; i++)
        pos[i] = (i - 1) / len + 1;

    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 1; i <= num; i++)
        for (int j = st[i]; j <= ed[j]; j++)
            sum[i] += arr[j];
    return 0;
}