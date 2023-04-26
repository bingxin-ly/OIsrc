#include <bits/stdc++.h>
using namespace std;

#define get(_) _ = read()
typedef long long loong;
inline loong read()
{
    loong p = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        p = p * 10 + c - '0', c = getchar();
    return p;
}

loong sum, d[160];
loong get_fac(int n)
{
    static map<int, loong> fac = {{0, 1}, {1, 1}};
    if (n < 0)
        return -1;
    if (fac.count(n))
        return fac[n];
    // 反向迭代器！！！
    int lastn = fac.crbegin()->first;
    loong lastv = fac.crbegin()->second;
    for (int i = lastn + 1; i <= n; i++)
        lastv *= i, fac[i] = lastv;
    return lastv;
}
int main()
{
    int get(n);
    for (int i = 1; i <= n; i++)
    {
        get(d[i]), sum += d[i] - 1;
        if (!d[i] && n != 1)
            puts("0"), exit(0);
        get_fac(d[i] - 1);
    }
    if (sum != n - 2)
        puts("0"), exit(0);

    loong ans = 1, j = 1;
    for (int i = 1; i <= n - 2; i++)
    {
        ans *= i;
        if (j > n)
            continue;
        if (!(ans % get_fac(d[j] - 1)))
            ans /= get_fac(d[j] - 1), j++;
    }
    printf("%lld", ans);
    return 0;
}