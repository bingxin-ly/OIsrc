#include <bits/stdc++.h>
using namespace std;

// 注意独立子问题
/* 当 n = 2 时，有一个角有障碍物，此时任何一块地毯均可填满
   当 n = 4 时，分成三个 2 * 2 的格子，其中一个已经有障碍物，
   余下三个在中间放一块地毯，便可构造为上面的三个问题 */

#define ul solve(bx + l - 1, by + l - 1, bx, by, l);
#define ur solve(bx + l - 1, by + l, bx, by + l, l);
#define dl solve(bx + l, by + l - 1, bx + l, by, l);
#define dr solve(bx + l, by + l, bx + l, by + l, l);

void solve(int x, int y, int bx, int by, int l)
{
    if (l == 1)
        return;
    l >>= 1;
    if (x - bx < l && y - by < l)
    {
        printf("%d %d 1\n", bx + l, by + l);
        solve(x, y, bx, by, l);
        ur dl dr
    }
    if (x - bx < l && y - by >= l)
    {
        printf("%d %d 2\n", bx + l, by + l - 1);
        solve(x, y, bx, by + l, l);
        ul dl dr
    }
    if (x - bx >= l && y - by < l)
    {
        printf("%d %d 3\n", bx + l - 1, by + l);
        solve(x, y, bx + l, by, l);
        ul ur dr
    }
    if (x - bx >= l && y - by >= l)
    {
        printf("%d %d 4\n", bx + l - 1, by + l - 1);
        solve(x, y, bx + l, by + l, l);
        ul ur dl
    }
}

signed main()
{
    int k, x, y;
    scanf("%d%d%d", &k, &x, &y);
    solve(x, y, 1, 1, 1 << k);
    return 0;
}