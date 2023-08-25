#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int N = 1e5 + 5;
struct plane
{
    int a, b;
} ps[N];
bool operator<(plane x, plane y) { return x.a < y.a; }
int n, m1, m2, ap[N], bp[N];

void calc(int m, int *res)
{
    priority_queue<pii, vector<pii>, greater<>> wat;
    priority_queue<int, vector<int>, greater<>> avi;
    for (int i = 1; i <= n; i++)
        avi.emplace(i);
    for (int i = 1, p; i <= m; i++)
    {
        while (!wat.empty() && ps[i].a > wat.top().first)
            avi.emplace(wat.top().second), wat.pop();
        if (avi.empty())
            continue;
        p = avi.top(), avi.pop();
        res[p] += 1, wat.emplace(ps[i].b, p);
    }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m1 >> m2;
    for (int i = 1; i <= m1; i++)
        cin >> ps[i].a >> ps[i].b;
    sort(ps + 1, ps + m1 + 1), calc(m1, ap);
    for (int i = 1; i <= m2; i++)
        cin >> ps[i].a >> ps[i].b;
    sort(ps + 1, ps + m2 + 1), calc(m2, bp);

    for (int i = 2; i <= n; i++)
        ap[i] += ap[i - 1], bp[i] += bp[i - 1];
    int ans = 0;
    for (int i = 0; i <= n; i++)
        ans = max(ans, ap[i] + bp[n - i]);
    cout << ans;
    return 0;
}