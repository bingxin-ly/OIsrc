#include <bits/stdc++.h>
using namespace std;
typedef long long loong;

int rs[11], ps[11]; // rs: 余数, ps: 模数
void exgcd(loong a, loong b, loong &x, loong &y)
{
    if (!b)
        return x = 1, y = 0, void();
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
loong CRT(int k)
{
    loong n = 1, ans = 0;
    for (int i = 1; i <= k; i++)
        n = n * ps[i];
    for (int i = 1; i <= k; i++)
    {
        loong m = n / ps[i], b, y;
        exgcd(m, ps[i], b, y); // b * m mod ps[i] = 1
        ans = (ans + rs[i] * m * b % n) % n;
    }
    return (ans % n + n) % n;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> ps[i] >> rs[i];
    cout << CRT(n);
    return 0;
}