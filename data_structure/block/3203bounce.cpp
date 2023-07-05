#include <bits/stdc++.h>
using namespace std;
inline void read(int &p)
{
    static int c;
    p = 0, c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

constexpr int N = 2e5 + 5, K = 450;
int n, m, arr[N];
int st[K], ed[K], stp[N], tow[N];

/* int edp;
int pre(int pos, int frt)
{
    if (pos > frt)
        return edp = pos, 0;
    stp[pos] = pre(pos + arr[pos], frt) + 1, tow[pos] = edp;
    return stp[pos];
} */
signed main()
{
    read(n);
    int len = sqrt(n), num = n / len;
    for (int i = 0; i < n; i++)
        read(arr[i]);
    for (int i = 0; i <= num; i++)
        st[i] = i * len, ed[i] = i * len + len - 1;
    ed[num] = n - 1;
    /* for (int i = 0; i < n; i++)
        if (!stp[i])
            pre(i, ed[i / len]); */
    // 把递归式的改成循环式的快好多好多（可惜不会化循环 kk
    for (int i = n - 1; ~i; i--)
        if (i + arr[i] >= ed[i / len])
            stp[i] = 1, tow[i] = i + arr[i];
        else
            stp[i] = stp[i + arr[i]] + 1,
            tow[i] = tow[i + arr[i]];

    read(m);
    for (int op, a, b, id; m--;)
    {
        read(op);
        if (op == 1)
        {
            read(a);
            int tims = 0;
            while (a < n)
                tims += stp[a], a = tow[a];
            write(tims), putchar('\n');
        }
        else
        {
            read(a), read(b);
            arr[a] = b, id = a / len;
            memset(stp + st[id], 0, len * sizeof(int));
            /* for (int i = st[id], up = ed[id]; i <= up; i++)
                if (!stp[i])
                    pre(i, up); */
            for (int i = ed[id]; i >= st[id]; i--)
                if (i + arr[i] >= ed[id])
                    stp[i] = 1, tow[i] = i + arr[i];
                else
                    stp[i] = stp[i + arr[i]] + 1,
                    tow[i] = tow[i + arr[i]];
        }
    }
    return 0;
}