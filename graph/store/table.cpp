#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int h[N],  // h 是表头的坐标
    e[N],  // e 存储的是值
    ne[N], // ne存储的是下一个点的坐标
    idx;   // idx 存储的是一个可以用的点的坐标

void add(int a, int b) // 有向边，a->b
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int main()
{
    int n, m;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
    }
    return 0;
}