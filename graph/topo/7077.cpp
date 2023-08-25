#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int N = 1e6 + 5, MOD = 998244353;
int n, m, Q, F[N];
int hed[N], nxt[N << 1], edg[N << 1], in[N], idx;
ll a[N];

inline void link(int u, int v)
{
    nxt[++idx] = hed[u], hed[u] = idx;
    edg[idx] = v, in[v]++;
}

struct oper
{
    int tp, p;
    ll v, mul, sum;
} b[N];

queue<int> q;
int ord[N], bnbn;
void toposort()
{
    for (int i = 1; i <= m; i++)
        if (!in[i])
            q.push(i);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        ord[++bnbn] = x;
        for (int i = hed[x]; i; i = nxt[i])
        {
            int y = edg[i];
            in[y]--;
            if (!in[y])
                q.push(y);
        }
    }
}

void getmul()
{
    for (int i = m; i; i--)
    {
        int x = ord[i];
        for (int j = hed[x]; j; j = nxt[j])
        {
            int y = edg[j];
            b[x].mul = b[x].mul * b[y].mul % MOD;
        }
    }
}

void getsum()
{
    for (int i = 1; i <= m; i++)
    {
        int x = ord[i];
        ll now = 1;
        for (int j = hed[x]; j; j = nxt[j])
        {
            int y = edg[j];
            b[y].sum = (b[y].sum + b[x].sum * now % MOD) % MOD;
            now = now * b[y].mul % MOD;
        }
    }
}

int main()
{
    cin >> (n);
    for (int i = 1; i <= n; i++)
        cin >> (a[i]);
    cin >> (m);
    for (int i = 1; i <= m; i++)
    {
        cin >> (b[i].tp);
        if (b[i].tp == 1)
        {
            cin >> (b[i].p);
            cin >> (b[i].v);
            b[i].mul = 1;
        }
        else if (b[i].tp == 2)
        {
            cin >> (b[i].v);
            b[i].mul = b[i].v;
        }
        else
        {
            cin >> (b[i].p);
            b[i].mul = 1;
            for (int j = 1, x; j <= b[i].p; j++)
            {
                cin >> (x);
                link(i, x);
            }
        }
    }
    toposort();
    getmul();
    cin >> Q;
    ll now = 1;
    for (int i = 1; i <= Q; i++)
        cin >> (F[i]);
    for (int i = Q; i; i--)
    {
        int x = F[i];
        b[x].sum = (b[x].sum + now) % MOD;
        now = now * b[x].mul % MOD;
    }
    getsum();
    for (int i = 1; i <= n; i++)
        a[i] = a[i] * now % MOD;
    for (int i = 1; i <= m; i++)
        if (b[i].tp == 1)
            a[b[i].p] = (a[b[i].p] + b[i].v * b[i].sum % MOD) % MOD;
    for (int i = 1; i <= n; i++)
        cout << a[i] << ' ';
    return 0;
}
