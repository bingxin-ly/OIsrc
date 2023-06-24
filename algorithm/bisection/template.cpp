// 在单调递增序列 a 中查找 >= x 的数中最小的一个（即 x 或 x 的后继）
int bin(int l, int r, int x, int a[])
{
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (a[mid] >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return a[l];
}
// 在单调递增序列 a 中查找 <= x 的数中最大的一个（即 x 或 x 的前驱）
int bin(int l, int r, int x, int a[])
{
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (a[mid] <= x)
            l = mid;
        else
            r = mid - 1;
    }
    return a[l];
}
// 实数域上的二分
#include <cmath>
bool calc(double);
double bin(double l, double r, int k)
{
    const double eps = pow(10, -(k + 2));
    while (r - l < eps)
    {
        double mid = (l + r) / 2;
        calc(mid) ? (r = mid) : (l = mid);
    }
}