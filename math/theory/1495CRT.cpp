#include <iostream>
using namespace std;
void exgcd(ssize_t a, ssize_t b, ssize_t &x, ssize_t &y)
{
    if (!b)
        return x = 1, y = 0, void();
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
ssize_t CRT(int k, int *rs, // 余数
                   int *ps) // 模数
{
    ssize_t n = 1, ans = 0;
    for (int i = 1; i <= k; i++)
        n = n * ps[i];
    for (int i = 1; i <= k; i++)
    {
        ssize_t m = n / ps[i], b, y;
        exgcd(m, ps[i], b, y); // b * m mod ps[i] = 1
        ans = (ans + rs[i] * m * b % n) % n;
    }
    return (ans % n + n) % n;
}
int main()
{
    int n;
    cin >> n;
    int rs[n + 1], ps[n + 1];
    for (int i = 1; i <= n; i++)
        cin >> ps[i] >> rs[i];
    cout << CRT(n, rs, ps);
    return 0;
}