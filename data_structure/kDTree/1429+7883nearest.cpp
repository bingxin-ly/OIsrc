#include <bits/stdc++.h>
using namespace std;
inline void ckmax(int &x, int y) { x = x > y ? x : y; }
inline void ckmin(int &x, int y) { x = x < y ? x : y; }
inline long long squ(long long x) { return x * x; }

constexpr int N = 4e5 + 5;
struct poi
{
    int ls, rs;
    int di[2], mx[2], mn[2];
} p[N], t[N];

void pushup(int p)
{
    int ls = t[p].ls, rs = t[p].rs;
    for (int i = 0; i <= 1; i++)
    {
        t[p].mx[i] = t[p].mn[i] = t[p].di[i];
        if (ls)
            ckmax(t[p].mx[i], t[ls].mx[i]),
                ckmin(t[p].mn[i], t[ls].mn[i]);
        if (rs)
            ckmax(t[p].mx[i], t[rs].mx[i]),
                ckmin(t[p].mn[i], t[rs].mn[i]);
    }
}
int build(int l, int r)
// 方差建树虽然麻烦，但是我喜欢，/yum🤤
{
    /* 我们提出两个优化：
    1. 选择的维度要满足其内部点的分布的差异度最大，
    即每次选择的切割维度是方差最大的维度。 // 就像劈一条木棍，肯定是拦腰劈
    2. 每次在维度上选择切割点时选择该维度上的 中位数，
    这样可以保证每次分成的左右子树大小尽量相等。
    可以发现，使用优化 2 后，构建出的 k-D Tree 的树高最多为 O(log n)。 */
    int mid = (l + r) >> 1;
    double av1 = 0, av2 = 0, va1 = 0, va2 = 0;
    for (int i = l; i <= r; i++)
        av1 += p[i].di[0], av2 += p[i].di[1];
    av1 /= r - l + 1, av2 /= r - l + 1;
    for (int i = l; i <= r; i++)
        va1 += squ(p[i].di[0] - av1), va2 += squ(p[i].di[1] - av2);
    nth_element(p + l, p + mid, p + r + 1, [d = va1 < va2](const poi &x, const poi &y)
                { return x.di[d] < y.di[d]; });
    t[mid] = p[mid];
    if (l < mid)
        t[mid].ls = build(l, mid - 1);
    if (r > mid)
        t[mid].rs = build(mid + 1, r);
    pushup(mid);
    return mid;
}
long long ans = 2e18;
long long dis(int x, int y)
{
    return squ(p[x].di[0] - p[y].di[0]) + squ(p[x].di[1] - p[y].di[1]);
}
long long cal(int x, int o)
{
    long long dx = max(max(p[x].di[0] - t[o].mx[0], t[o].mn[0] - p[x].di[0]), 0),
              dy = max(max(p[x].di[1] - t[o].mx[1], t[o].mn[1] - p[x].di[1]), 0);
    return squ(dx) + squ(dy);
}
void query(int l, int r, int x)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    if (mid != x)
        ans = min(ans, dis(x, mid)); // 只有这句是更新答案
    if (l == r)
        return; // 我已经是叶子了，我是不是……就到这里了
    long long disl = cal(x, t[mid].ls), disr = cal(x, t[mid].rs);
    if (disl < ans && disr < ans)
    // 无法确定要进入哪个子树，需要递归求解
    {
        if (disl < disr)
        // 距离作为启发式函数，先搜更近的
        {
            query(l, mid - 1, x);
            disr < ans && (query(mid + 1, r, x), true);
        }
        else
        {
            query(mid + 1, r, x);
            disl < ans && (query(l, mid - 1, x), true);
        }
    }
    else if (disl < ans) // 然后那个可能更新答案就去哪个里边
        query(l, mid - 1, x);
    else if (disr < ans)
        query(mid + 1, r, x);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].di[0] >> p[i].di[1];
    build(1, n);
    for (int i = 1; i <= n; i++)
        query(1, n, i);
    cout << /* fixed << setprecision(4) << sqrt */(ans);
    return 0;
}