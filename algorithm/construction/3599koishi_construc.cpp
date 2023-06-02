#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

const int N = 1e5 + 10;
bool is_prime[N];
void sieve(int n)
{
    memset(is_prime, true, n + 1);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2, up = sqrt(n); i <= up; ++i)
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
}

int fpow(int a, int k, int p)
{
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

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int x, t, n;
    cin >> x >> t;
    if (x == 1)
        goto A;
    else
        goto B;
A:
    while (t--)
    {
        cin >> n;
        if (n % 2 && n != 1)
            cout << "0\n";
        else
        {
            cout << "2 ";
            for (int i = 0; i < n; i++)
                cout << n * !(i % 2) + (i % 2 ? 1 : -1) * i << ' ';
            cout << endl;
        }
    }
    return 0;
B:
    sieve(N), is_prime[4] = true;
    while (t--)
    {
        cin >> n;
        if (!is_prime[n])
            cout << "0\n";
        else
        {
            cout << "2 1 ";
            if (n == 4)
                cout << "3 2 4\n";
            else
            {
                for (int i = 2; i < n; i++)
                    cout << i * fpow(i - 1, n - 2, n) % n << ' ';
                cout << n << endl;
            }
        }
    }
    return 0;
}