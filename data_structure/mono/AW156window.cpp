#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
namespace C
{
    int a[N], q[N];
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        int h = 0, t = -1;
        for (int i = 1; i <= n; i++)
        {
            if (h <= t && q[h] <= i - k)
                h++;
            while (h <= t && a[q[t]] >= a[i])
                t--;
            q[++t] = i;
            if (i >= k)
                cout << a[q[h]] << ' ';
        }
        cout << '\n';
        h = 0, t = -1;
        for (int i = 1; i <= n; i++)
        {
            if (h <= t && q[h] <= i - k)
                h++;
            while (h <= t && a[q[t]] <= a[i])
                t--;
            q[++t] = i;
            if (i >= k)
                cout << a[q[h]] << ' ';
        }
        return 0;
    }
}
namespace CPP
{
    int n, k, a[N];
    void solve(auto cmp)
    {
        deque<int> q;
        for (int i = 1; i <= n; i++)
        {
            if (!q.empty() && q.front() <= i - k)
                q.pop_front();
            while (!q.empty() && cmp(a[q.back()], a[i]))
                q.pop_back();
            q.emplace_back(i);
            if (i >= k)
                cout << a[q.front()] << ' ';
        }
        cout << '\n';
    }
    signed main()
    {
        ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        solve([](auto x, auto y) { return x >= y; });
        solve([](auto x, auto y) { return x <= y; });
        return 0;
    }
}
signed main() { return CPP::main(); }