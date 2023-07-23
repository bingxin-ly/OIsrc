#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m;
struct val
{
    int num, idx;
    inline bool operator<(const val &o) const
    {
        if (num != o.num)
            return num < o.num;
        return num > 0 ? idx < o.idx : idx > o.idx;
    }
} seq[N];

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> seq[i].num, seq[i].idx = i;
    sort(seq + 1, seq + n + 1);
    for (int i = 1; i <= n; i++)
        cout << seq[i].idx << ' ';
    return 0;
}