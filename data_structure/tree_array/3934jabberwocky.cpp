#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 10, MAX = 2e7;
int prime[MAX + 10], phi[MAX + 10];
bool st[MAX + 10];

void prephi()
{
    int cnt = 0;
    phi[1] = 1;

    for (int i = 2; i <= MAX; i++)
    {
        if (!st[i])
        {
            prime[++cnt] = i;
            phi[i] = i - 1;
        }

        for (int j = 1; j <= cnt; j++)
        {
            int t = i * prime[j];
            if (t > MAX)
                break;
            st[t] = true;

            if (i % prime[j] == 0)
            {
                phi[t] = phi[i] * prime[j];
                break;
            }

            phi[t] = phi[i] * (prime[j] - 1);
        }
    }
}

typedef pair<int, bool> num;
num fpow(int a, int k, int p)
{
    num res{1, a >= p};
    a %= p;

    while (k)
    {
        if (k & 1)
            res.first *= a;
        if (res.first >= p)
            res.first %= p, res.second = true;

        a *= a;
        if (a >= p)
            a %= p, res.second = true;
        k >>= 1;
    }
    return res;
}

int n, arr[N];
inline int lowbit(int x) { return x & -x; }
void modify(int p, int x)
{
    for (; p <= n; p += lowbit(p))
        arr[p] += x;
}
void add(int l, int r, int x)
{
    modify(l, x);
    modify(r + 1, -x);
}
int query(int p)
{
    int res = 0;
    for (; p; p -= lowbit(p))
        res += arr[p];
    return res;
}
num solve(int l, int r, int p)
{
    int al = query(l);
    if (p == 1)
        return {0, true};
    if (al == 1)
        return {1, false};
    if (l == r)
        return {al % p, al >= p};
    num res = solve(l + 1, r, phi[p]);
    res.first += res.second * phi[p];
    return fpow(al, res.first, p);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int m;
    cin >> n >> m;
    prephi();
    for (int i = 1, x; i <= n; i++)
        cin >> x, add(i, i, x);
    while (m--)
    {
        int op, l, r, x;
        cin >> op >> l >> r >> x;
        if (op == 1)
            add(l, r, x);
        else
            cout << solve(l, r, x).first << '\n';
    }
    return 0;
}