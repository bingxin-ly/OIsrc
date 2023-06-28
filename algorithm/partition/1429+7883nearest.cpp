#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 4e5 + 10;
struct
{
    int x, y;
} points[N];
int middle[N];

inline int min(int a, int b) { return a < b ? a : b; }
inline int square(int a) { return a * a; }
inline int calc_dist(int i, int j)
{
    auto x = square(points[i].x - points[j].x),
         y = square(points[i].y - points[j].y);
    return x + y;
}
int merge(int left, int right)
{
    int dis = LLONG_MAX;
    if (left == right)
        return dis;
    if (left + 1 == right)
        return calc_dist(left, right);

    int mid = (left + right) >> 1;
    dis = min(merge(left, mid), merge(mid + 1, right));

    int poi = 0;
    for (int i = left; i <= right; i++)
        if (abs(points[mid].x - points[i].x) < sqrt(dis))
            middle[poi++] = i;
    sort(middle, middle + poi, [](int a, int b)
         { return points[a].y < points[b].y; });

    for (int i = 0; i < poi; i++)
        for (int j = i + 1;
             j < poi && points[middle[j]].y - points[middle[i]].y < sqrt(dis);
             j++)
            dis = min(dis, calc_dist(middle[i], middle[j]));
    return dis;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> points[i].x >> points[i].y;
    sort(points, points + n, [](const auto &a, const auto &b)
         { return a.x == b.x ? a.y < b.y : a.x < b.x; });

    cout << fixed << setprecision(0) << /* sqrt */ (merge(0, n - 1));
    return 0;
}