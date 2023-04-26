#include <bits/stdc++.h>
#define chkmax(a, b) b > a ? a = b : a
using namespace std;

namespace Maker
{
    unsigned int x0, seed;
    void init() { scanf("%u%u", &x0, &seed); }
    inline unsigned int getnum()
    {
        x0 = (x0 << 3) ^ x0;
        x0 = ((x0 >> 5) + seed) ^ x0;
        return x0;
    }
}

const int N = 1e5 + 10;
int n, m;
unsigned ST[N][21], lg2[N];

inline void pre()
{
    for (int i = 2; i <= n; i++)
        lg2[i] = lg2[i >> 1] + 1;
}
inline void modify(int l, int r, unsigned v)
{
    int k = lg2[r - l + 1];
    chkmax(ST[l][k], v), chkmax(ST[r - (1 << k) + 1][k], v);
}
inline void proc()
{
    for (int len = 16; len >= 1; len--)
        for (int i = 1; i + (1 << len) - 1 <= n; i++)
            chkmax(ST[i][len - 1], ST[i][len]), chkmax(ST[i + (1 << (len - 1))][len - 1], ST[i][len]);
}

int main()
{
    int typ;
    scanf("%d%d%d", &n, &m, &typ);
    for (int i = 1; i <= n; i++)
        scanf("%u", &ST[i][0]);
    pre();

    Maker::init();
    for (int i = 1; i <= m; ++i)
    {
        int l = Maker::getnum() % n + 1, r = Maker::getnum() % n + 1;
        unsigned int v = Maker::getnum();
        if (l > r)
            swap(l, r);
        if (typ == 1)
            l = 1;

        modify(l, r, v);
    }
    proc();

    for (int i = 1; i <= n; i++)
        printf("%u ", ST[i][0]);
    return 0;
}
