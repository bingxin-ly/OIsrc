#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 10;
struct road
{
    int x, y, t;
    bool operator<(const road &other) const
    {
        return t < other.t;
    }
} roads[MAX];
int n, m, f[MAX];

int find(int x)
{
    return f[x] == x ? x : (f[x] = find(f[x]));
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
        cin >> roads[i].x >> roads[i].y >> roads[i].t;
    sort(roads + 1, roads + m + 1);

    for (int i = 1; i <= n; i++)
        f[i] = i;
    for (int i = 1; i <= m; i++)
    {
        int fx = find(roads[i].x), fy = find(roads[i].y);
        if (fx != fy)
            f[fx] = fy, n--;
        if (n == 1)
        {
            cout << roads[i].t;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
