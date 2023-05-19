// 可持久化 Trie
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'),
            x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

const int N = 6e5 + 10;
int idx, tr[N * 24][2], latest[N * 24];
int s[N], root[N];

void insert(int i, int k, int p, int q)
{
    if (k < 0)
        return latest[q] = i, void();
    int v = s[i] >> k & 1;
    if (p)
        tr[q][v ^ 1] = tr[p][v ^ 1];
    tr[q][v] = ++idx;
    insert(i, k - 1, tr[p][v], tr[q][v]);
    latest[q] = max(latest[tr[q][0]], latest[tr[q][1]]);
}

int query(int rt, int val, int k, int l)
{
    if (k < 0)
        return s[latest[rt]] ^ val;
    int c = val >> k & 1;
    if (latest[tr[rt][c ^ 1]] >= l)
        return query(tr[rt][c ^ 1], val, k - 1, l);
    else
        return query(tr[rt][c], val, k - 1, l);
}
/* int query(int rt, int c, int l)
{
    int p = rt;
    for (int i = 23; i >= 0; i--)
    {
        int v = c >> i & 1;
        if (latest[tr[p][v ^ 1]] >= l)
            p = tr[p][v ^ 1];
        else
            p = tr[p][v];
    }
    return c ^ s[latest[p]];
} */

int main()
{
    int n(read()), m(read());
    latest[0] = -1, root[0] = ++idx;
    insert(0, 23, 0, root[0]);
    for (int i = 1, x; i <= n; i++)
    {
        x = read();
        s[i] = s[i - 1] ^ x;
        root[i] = ++idx;
        insert(i, 23, root[i - 1], root[i]);
    }

    while (m--)
    {
        char op = getchar();
        while (!isalpha(op))
            op = getchar();
        if (op == 'A')
        {
            int x = read();
            root[++n] = ++idx;
            s[n] = s[n - 1] ^ x;
            insert(n, 23, root[n - 1], root[n]);
        }
        else
        {
            int l(read()), r(read()), x(read());
            write(query(root[r - 1], s[n] ^ x, 23, l - 1)), putchar('\n');
        }
    }
    return 0;
}