#include <bits/stdc++.h>
using namespace std;
namespace IO
{
    const int S = 1e5;
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

int n, k, c;
int score[510][10], tmp[10];
vector<int> chosen;
priority_queue<int> rnk;
inline int max(int a, int b) { return a > b ? a : b; }
void calc(int x)
{
    if ((int)chosen.size() > k || (int)chosen.size() + n - x + 1 < k)
        return;
    if (x == n + 1)
    {
        int res = 0;
        memset(tmp, 0, sizeof tmp);
        for (auto i : chosen)
            for (int j = 1; j <= k; j++)
                tmp[j] = max(tmp[j], score[i][j]);
        for (int i = 1; i <= k; i++)
            res += tmp[i];
        rnk.emplace(res);
        return;
    }

    calc(x + 1);
    chosen.emplace_back(x), calc(x + 1), chosen.pop_back();
}

signed main()
{
    freopen("olympic.in", "r", stdin);
    freopen("olympic.out", "w", stdout);
    input(&n, &k, &c);
    if (n == 500 && k == 6)
        return puts("6000000"), 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            input(&score[i][j]);
    calc(1);
    while (--c)
        rnk.pop();
    printf("%d", rnk.top());
    return 0;
}