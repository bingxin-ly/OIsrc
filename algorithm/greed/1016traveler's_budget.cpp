#include <bits/stdc++.h>
using namespace std;

int N;
double D1, D2, C, P, res, ans, maxx;
struct node
{
    double co, dis;
} pl[100010];

int Solve(int now)
{
    int flag = INT_MAX;
    double d = pl[now].dis;
    for (int i = now + 1; i <= N && pl[i].dis - d <= maxx; i++)
    {
        if (pl[i].co < pl[now].co)
        {
            ans += ((pl[i].dis - d - res) / D2) * pl[now].co;
            res = 0;
            return i;
        }
        if (flag == INT_MAX || pl[i].co < pl[flag].co)
            flag = i;
    }
    if (D1 - pl[now].dis <= maxx)
    {
        ans += ((D1 - pl[now].dis - res) / D2) * pl[now].co;
        return INT_MAX;
    }
    if (flag == INT_MAX)
        printf("No Solution\n"), exit(0);
    ans += C * pl[now].co;
    res += (maxx - (pl[flag].dis - d));
    return flag;
}

int main()
{
    cin >> D1 >> C >> D2 >> P >> N;
    pl[0].dis = 0, pl[0].co = P;
    for (int i = 1; i <= N; i++)
        cin >> pl[i].dis >> pl[i].co;
    sort(pl, pl + N + 1, [](const auto &a, const auto &b)
         { return a.dis < b.dis; });
    maxx = C * D2;
    int t = 0;
    while (t != INT_MAX)
        t = Solve(t);
    printf("%.2lf", ans);
    return 0;
}
