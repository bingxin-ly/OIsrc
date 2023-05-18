#include <cstdio>
#define int long long
using namespace std;

int m, mem[10000002];
int f(int i)
{
    if (mem[i])
        return mem[i]; // 调取记忆
    if (i == 1 || i == 2)
        return mem[i] = 1 % m;
    else
        return mem[i] = (f(i - 1) + f(i - 2)) % m;
}
signed main()
{
    scanf("%lld", &m);
    int i = 1;
    while (f(i) != 0 || f(i + 1) != 1)
        i++;
    printf("%lld", i);
    return 0;
}
