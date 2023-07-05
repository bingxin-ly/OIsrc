#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\.in");
ofstream fout("D:\\OIsrc\\.out");
#define cin fin
#define cout fout
#endif

constexpr int N = 5e4 + 5;
int n;
namespace BIT
{
    int res[N];
    double sol[N];
    inline int lowbit(int x) { return x & -x; }
    void upd(int p, int v, double f)
    {
        for (; p <= n; p += lowbit(p))
            if (res[p] < v)
                res[p] = v, sol[p] = f;
            else if (res[p] == v)
                sol[p] += f;
    }
    int rquery(int p)
    {
        int ret = 0;
        for (; p; p -= lowbit(p))
            ret = max(ret, res[p]);
        return ret;
    }
    double fquery(int p, int v)
    {
        double ret = 0;
        for (; p; p -= lowbit(p))
            if (res[p] == v)
                ret += sol[p];
        return ret;
    }
    void del(int p)
    {
        for (; p <= n; p += lowbit(p))
            res[p] = sol[p] = 0;
    }
}
struct ele
{
    int x, y, z, res;
    double sol;
} s[N];

bool tag;
// 题意中的排序是 x > x, y > y, z < z shaber
auto cmp1 = [](const ele &a, const ele &b)
{ return a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y > b.y) : a.x > b.x; };
auto cmp2 = [](const ele &a, const ele &b)
{ return a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y < b.y) : a.x < b.x; };
void cdq(int l, int r)
{
    static auto cmpy = [](const ele &a, const ele &b)
    { return (a.y > b.y) ^ tag; };
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    stable_sort(s + l, s + mid + 1, cmpy), stable_sort(s + mid + 1, s + r + 1, cmpy);

    int i = l, j = mid + 1;
    while (j <= r)
    {
        while (i <= mid && (!tag ? s[i].y >= s[j].y : s[i].y <= s[j].y))
            BIT::upd(s[i].z, s[i].res, s[i].sol), i++;
        int tmp = BIT::rquery(s[j].z) + 1;
        if (s[j].res < tmp)
            s[j].res = tmp, s[j].sol = BIT::fquery(s[j].z, tmp - 1);
        else if (s[j].res == tmp)
            s[j].sol += BIT::fquery(s[j].z, tmp - 1);
        j++;
    }
    for (int k = l; k < i; k++)
        BIT::del(s[k].z);

    sort(s + mid + 1, s + r + 1, !tag ? cmp1 : cmp2);
    cdq(mid + 1, r);
}

int f1[N], f2[N];
double g1[N], g2[N];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].x >> s[i].y, s[i].z = i;
        s[i].res = s[i].sol = 1;
    }

    tag = false;
    sort(s + 1, s + n + 1, cmp1), cdq(1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        f1[s[i].z] = s[i].res, g1[s[i].z] = s[i].sol,
        ans = max(ans, f1[s[i].z]);
    cout << ans << '\n';
    for (int i = 1; i <= n; i++)
        s[i].z = n - s[i].z + 1, s[i].res = s[i].sol = 1;

    tag = true;
    sort(s + 1, s + n + 1, cmp2), cdq(1, n);
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        f2[n - s[i].z + 1] = s[i].res, g2[n - s[i].z + 1] = s[i].sol;
        if (f2[n - s[i].z + 1] == ans)
            sum += g2[n - s[i].z + 1];
    }

    for (int i = 1; i <= n; i++)
        cout << fixed << setprecision(5)
             << (f1[i] + f2[i] == ans + 1 ? g1[i] * g2[i] / sum : 0.0) << ' ';
    return 0;
}