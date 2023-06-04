#include <bits/stdc++.h>
using namespace std;


#define ul dfs(bx + l - 1, by + l - 1, bx, by, l); // 递归做左上角
#define ur dfs(bx + l - 1, by + l, bx, by + l, l); // 递归做右上角
#define dl dfs(bx + l, by + l - 1, bx + l, by, l); // 递归做左下角
#define dr dfs(bx + l, by + l, bx + l, by + l, l); // 递归做右下角

void dfs(int x, int y, int bx, int by, int l)
{
    if (l == 1)
        return;
    l >>= 1;
    // 左上角
    if (x - bx < l && y - by < l)
    {
        // 输出
        printf("%d %d 1\n", bx + l, by + l);
        dfs(x, y, bx, by, l); // 继续把有人的区块填满
        // 按定理处理大方块
        ur
            dl
                dr
    }
    // 右上角
    if (x - bx < l && y - by >= l)
    {
        // 输出
        printf("%d %d 2\n", bx + l, by + l - 1);
        dfs(x, y, bx, by + l, l); // 继续把有人的区块填满
        // 按定理处理大方块
        ul
            dl
                dr
    }
    // 左下角
    if (x - bx >= l && y - by < l)
    {
        // 输出
        printf("%d %d 3\n", bx + l - 1, by + l);
        dfs(x, y, bx + l, by, l); // 继续把有人的区块填满
        // 按定理处理大方块
        ul
            ur
                dr
    }
    // 右下角
    if (x - bx >= l && y - by >= l)
    {
        // 输出
        printf("%d %d 4\n", bx + l - 1, by + l - 1);
        dfs(x, y, bx + l, by + l, l); // 继续把有人的区块填满
        // 按定理处理大方块
        ul
            ur
                dl
    }
}

int main()
{
    int k, x, y;
    scanf("%d%d%d", &k, &x, &y);
    dfs(x, y, 1, 1, 1 << k);
    return 0;
}
