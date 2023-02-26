struct edge
{
    int to, // 指向边的终点
        w,  // 边的权值
        ne; // 指向下一条边
} e[N];
int idx,  // 存储可以用的点的坐标
    h[N]; // 表头的坐标

void add(int a, int b, int ww = 1) // 有向边，a->b
{
    e[++idx].to = b; // 注意自增++的位置！！
    e[idx].ne = h[a];
    e[idx].w = ww;
    h[a] = idx;
}
