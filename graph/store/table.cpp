int h[N], e[N], ne[N], idx;
/* h 是表头的坐标
   e 存储的是值
   ne存储的是下一个点的坐标
   idx 存储的是一个可以用的点的坐标 */

void add(int a, int b) // 有向边，a->b
{
    e[++idx] = b; // 注意自增++的位置！！
    ne[idx] = h[a];
    h[a] = idx;
}
