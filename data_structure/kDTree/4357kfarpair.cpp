#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
long long n, k;
#define x first
#define y second
pair<long long, long long> ps[N];
priority_queue<long long, vector<long long>, greater<>> q;

long long ls[N], rs[N], L[N], R[N], D[N], U[N]; // left/right/down/up
inline long long squ(long long $) { return $ * $; }
void maintain(int u)
{
    L[u] = R[u] = ps[u].x;
    D[u] = U[u] = ps[u].y;
    if (ls[u])
        L[u] = min(L[u], L[ls[u]]), R[u] = max(R[u], R[ls[u]]),
        D[u] = min(D[u], D[ls[u]]), U[u] = max(U[u], U[ls[u]]);
    if (rs[u])
        L[u] = min(L[u], L[rs[u]]), R[u] = max(R[u], R[rs[u]]),
        D[u] = min(D[u], D[rs[u]]), U[u] = max(U[u], U[rs[u]]);
}
int build(int l, int r)
{
    if (l > r)
        return 0;
    int mid = (l + r) >> 1;
    double av1 = 0, av2 = 0, va1 = 0, va2 = 0; // average variance
    for (int i = l; i <= r; i++)
        av1 += ps[i].x, av2 += ps[i].y;
    av1 /= (r - l + 1), av2 /= (r - l + 1);
    for (int i = l; i <= r; i++)
        va1 += squ(av1 - ps[i].x), va2 += squ(av2 - ps[i].y);
    nth_element(ps + l, ps + mid, ps + r + 1,
                [va1, va2](const auto &a, const auto &b)
                { return va1 > va2 ? a.x < b.x : a.y < b.y; });
    ls[mid] = build(l, mid - 1), rs[mid] = build(mid + 1, r);
    maintain(mid);
    return mid;
}

inline long long dist(int a, int b)
{
    return max(squ(ps[a].x - L[b]), squ(ps[a].x - R[b])) +
           max(squ(ps[a].y - D[b]), squ(ps[a].y - U[b]));
}
void query(int l, int r, int pos)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    long long dis = squ(ps[mid].x - ps[pos].x) + squ(ps[mid].y - ps[pos].y);
    if (dis > q.top())
        q.pop(), q.push(dis);
    long long disl = dist(pos, ls[mid]), disr = dist(pos, rs[mid]);
    if (disl > q.top() && disr > q.top())
        if (disl > disr)
        {
            query(l, mid - 1, pos);
            if (disl > q.top())
                query(mid + 1, r, pos);
        }
        else
        {
            query(mid + 1, r, pos);
            if (disl > q.top())
                query(l, mid - 1, pos);
        }
    else
    {
        if (disl > q.top())
            query(l, mid - 1, pos);
        if (disr > q.top())
            query(mid + 1, r, pos);
    }
}

signed main()
{
    cin >> n >> k;
    k <<= 1;
    for (int i = 1; i <= k; i++)
        q.push(0);
    for (int i = 1; i <= n; i++)
        cin >> ps[i].x >> ps[i].y;
    build(1, n);
    for (int i = 1; i <= n; i++)
        query(1, n, i);
    cout << q.top() << '\n';
    return 0;
}