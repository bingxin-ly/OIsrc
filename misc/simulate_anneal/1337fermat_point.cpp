// 概率 = e ^ (-deltaE/T)
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef pair<double, double> pdd;

int n, w[1010];
pdd a[1010];
double ans = 1e18, ansx, ansy;

double rand(double l, double r)
{
    return (double)rand() / RAND_MAX * (r - l) + l;
}

double dis(pdd a, pdd b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double calc(pdd now)
{
    double res = 0;
    for (int i = 1; i <= n; i++)
        res += dis(now, a[i]) * w[i];
    // ans = min(ans, res);
    if (res < ans)
        ans = res, ansx = now.x, ansy = now.y;
    return res;
}

void simulate()
{
    pdd cur(rand(0, 10000), rand(0, 10000));
    for (double t = 1e4; t >= 1e-4; t *= 0.98)
    {
        pdd now(rand(cur.x - t, cur.x + t), rand(cur.y - t, cur.y + t));
        double delta = calc(now) - calc(cur);
        if (exp(-delta / t) > rand(0, 1))
            cur = now;
    }
}

int main()
{
    double st = 1.0 * clock() / CLOCKS_PER_SEC;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].y >> w[i];
    // for (int i = 1; i <= 1000; i++)
    while (1.0 * clock() / CLOCKS_PER_SEC - st < 0.95)
        simulate();

    printf("%.3lf %.3lf\n", ansx, ansy);
    return 0;
}
