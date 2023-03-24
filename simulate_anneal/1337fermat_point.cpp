#include <bits/stdc++.h>
using namespace std;

const int N = 1e4+10;
int n, x[N], y[N], w[N];
double ansx, ansy, dis;

mt19937 rd(time(0));
auto getrd = [](){ return 1.0*rd()/UINT32_MAX; };

double calc(double xx, double yy)
{
    double res = 0;
    for (int i = 1; i <= n; i++)
    {
        double dx = x[i] - xx, dy = y[i] - yy;
        res += sqrt(dx * dx + dy * dy) * w[i];
    }
    return res;
}

void simulate_anneal()
{
    double nowx = ansx, nowy = ansy;
    for (int t = 1e4; t > 1e-4; t *= 0.99)
    {
        double nxtx
    }
}