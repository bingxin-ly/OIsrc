#include <bits/stdc++.h>
using namespace std;
namespace IO
{
    const int S = 1e6;
    char B[S], *H = B, *T = B;
    inline int gc() { return (H == T) && (T = (H = B) + fread(B, 1, S, stdin), H == T) ? EOF : *H++; }
    template <typename T = int>
    inline T input(T *p = nullptr)
    {
        static T *o = new T;
        !p && (p = o), *p = 0;
        int c;
        while ((c = gc()) < '0' || c > '9')
            ;
        *p = c ^ '0';
        while ((c = gc()) >= '0' && c <= '9')
            *p = *p * 10 + (c ^ '0');
        return *p;
    }
    template <typename T, typename... Args>
    inline void input(T *p, Args... args) { input(p), input(args...); }
}
using IO::input;

const int N = 2e5 + 10;
priority_queue<vector<int>> poss;
vector<int> cur;

signed main()
{
    freopen("exchange.in", "r", stdin);
    freopen("exchange.out", "w", stdout);
    int n = input();
    cur.emplace_back(0x3f3f3f3f);
    vector<int> v;
    for (int i = 1; i <= n; i++)
        v.emplace_back(input());
    poss.emplace(v);

    for (int k = 2; k <= n; k++)
    {
        int pos = (k >> 1) - 2;
        if (pos >= 0)
        {
            int mn = cur[pos];
            while (poss.top()[pos] > mn)
                poss.pop();
        }
        vector<vector<int>> tmp;
        while (!poss.empty())
        {
            auto t = poss.top();
            poss.pop();
            tmp.emplace_back(t);
            swap(t[(k >> 1) - 1], t[k - 1]);
            cur = min(cur, t);
            tmp.emplace_back(t);
        }
        for (const auto &i : tmp)
            poss.emplace(i);
    }
    for (auto i : cur)
        printf("%d ", i);
    return 0;
}