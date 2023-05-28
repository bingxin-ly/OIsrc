#include <bits/stdc++.h>
using namespace std;

double a, b, c, d, eps = 1e-5;
double calc(double x)
{
    return a * x * x * x + b * x * x + c * x + d;
}
signed main()
{
    scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
    for (int i = -100; i < 100; i++)
    {
        // 值 > 0 无根，<= 0 有根
        double l = i, r = i + 1 - eps;
        if (calc(l) * calc(r) > eps) // > eps 即大于 0
            continue;
        while (r - l > eps)
        {
            double mid = (l + r) / 2;
            if (calc(mid) * calc(r) < eps) // 不是对 mid 的检验，而是勘根公式的再应用
                l = mid;                   // 其他地方也有检验一个区间而不是 mid 值的应用
            else
                r = mid;
        }
        printf("%.2lf ", l);
    }
    return 0;
}