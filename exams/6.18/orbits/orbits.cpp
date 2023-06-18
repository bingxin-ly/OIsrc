#include <bits/stdc++.h>
using namespace std;

const int M = 1e9 + 10, MOD = 10007;
int ava;
bool is_prime[M];

void sieve(int m, const vector<int> &fac)
{
    memset(is_prime, true, sizeof is_prime);

    for (int i : fac)
        for (int j = i; j <= m; j += i)
            is_prime[j] = false;

    for (int i = 1; i <= m; i++)
        ava += is_prime[i];
}

int C[3010][3010];
void initC(int n)
{
    for (int i = 1; i <= n; i++)
        C[i][1] = C[i][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 2; j < n; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
}
int fpow(int a, int k, int p)
{
    a %= p;
    int res = 1;
    while (k)
    {
        if (k & 1)
            res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}
stack<int> minn;
int n, m, facn, ans;
void sear(int x)
{
    queue<pair<int, int>> q;
    for (int i = 2, up = sqrt(x); i <= up; i++)
        if (!(x % i) && (minn.empty() || i >= minn.top()))
        {
            q.emplace(i, x / i);
            if (x / i <= m)
            {
                int now = minn.size() + 2;
                if (now == n)
                    ans += 1;
                else
                {
                    int cases = fpow(ava, n - now, MOD);
                    (ans += cases * facn % MOD) %= MOD;
                }
            }
        }

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        minn.push(t.first);
        sear(t.second);
        minn.pop();
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int k;
    cin >> n >> m >> k;
    int ok = k;
    facn = 1;
    for (int i = 2; i <= n; i++)
        (facn *= i) %= MOD;

    vector<int> fac;
    for (int i = 2, up = sqrt(k); i <= up; i++)
        if (!(k % i))
        {
            fac.emplace_back(i);
            while (!(k % i))
                k /= i;
        }
    if (k != 1)
        fac.emplace_back(k);
    sieve(m, fac);

    initC(n);
    sear(ok);
    if (ok <= m)
    {
        int cases = C[ava][n - 1];
        (ans += cases * facn % MOD) %= MOD;
    }
    cout << ans;
    return 0;
}