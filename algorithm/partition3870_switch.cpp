#include <bits/stdc++.h>
using namespace std;

bool lights[100010];
int n, m;
int sq;

struct block
{
    int l, r;
    int open, close;
    int n;
    void swp()
    {
        swap(open, close);
    }
} blocks[400];

void modify(int l, int r)
{
    int pos = 1;
    while (blocks[pos].l > l || l > blocks[pos].r)
        pos++;
    int san = blocks[pos].r - l + 1;
    //    blocks[pos].open -= san * w, blocks[pos].close += san * w;
    for (int i = l; i <= blocks[pos].r; i++)
    {
        if (lights[l])
            blocks[pos].open--, blocks[pos].close++;
        else
            blocks[pos].open++, blocks[pos].close--;
        lights[i] ^= 1;
    }
    while (blocks[++pos].r && blocks[pos].r <= r)
        blocks[pos].swp(), blocks[pos].n++;
    san = r - blocks[pos - 1].r;
    //    blocks[pos].open -= san * w, blocks[pos].close += san * w;
    if (san)
        for (int i = r - san + 1; i <= r; i++)
        {
            if (lights[l])
                blocks[pos].open--, blocks[pos].close++;
            else
                blocks[pos].open++, blocks[pos].close--;
            lights[i] ^= 1;
        }
}
int query(int l, int r)
{
    int ret = 0, pos = 1;
    while (blocks[pos].l > l || l > blocks[pos].r)
        pos++;
    int w = (blocks[pos].n + 1) % 2;
    for (int i = l; l <= blocks[i].r; i++)
        ret += (lights[i] == w);
    while (blocks[++pos].r <= r - sq)
        ret += blocks[pos].open;
    w = (blocks[pos].n + 1) % 2;
    for (int i = blocks[pos - 1].r + 1; i <= r; i++)
        ret += (lights[i] == w);
    return ret;
}
int main()
{
    cin >> n >> m;
    sq = sqrt(n);
    int p = 1;
    for (; blocks[p - 1].r + sq <= n; p++)
    {
        blocks[p].l = sq * (p - 1) + 1;
        blocks[p].r = min(sq * p, n);
        blocks[p].close = sq;
    }
    if (n % sq)
        blocks[p].l = n - n % sq + 1, blocks[p].r = n, blocks[p].close = n - blocks[p].l + 1;
    int op, a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> op >> a >> b;
        if (op == 0)
            modify(a, b);
        else
            cout << query(a, b) << endl;
    }
    return 0;
}