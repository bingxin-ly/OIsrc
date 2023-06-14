#include <bits/stdc++.h>
using namespace std;

inline int input()
{
    int p = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        p = p * 10 + c - '0', c = getchar();
    return p;
}

const int N = 5e5 + 10;
multiset<int> full, diff;
int st[N], ed[N];
int n, m, minn = INT_MAX;
void updmin(int x)
{
    auto it = full.lower_bound(x);
    int tmp = *it - x;
    it--;
    minn = min(minn, min(tmp, x - *it));
    full.insert(x);
}
void upddiff(int pos, int x)
{
    diff.insert(abs(x - ed[pos]));
    if (pos != n)
        diff.erase(diff.find(abs(st[pos + 1] - ed[pos]))),
            diff.insert(abs(st[pos + 1] - x));
    ed[pos] = x;
}

int main()
{
    n = input(), m = input();
    for (int i = 1; i <= n; i++)
        st[i] = ed[i] = input();

    full.insert(0x3fffffff), full.insert(~0x3fffffff);
    for (int i = 1; i < n; i++)
        diff.insert(abs(st[i + 1] - ed[i]));
    for (int i = 1; i <= n; i++)
        updmin(st[i]);
    for (int i = 1, pos, x; i <= m; i++)
    {
        char opt[16];
        scanf("%s", opt);
        switch (opt[4])
        {
        case 'R':
            pos = input(), x = input();
            updmin(x), upddiff(pos, x);
            break;
        case 'S':
            printf("%d\n", minn);
            break;
        case 'G':
            printf("%d\n", *diff.begin());
            break;
        }
    }
    return 0;
}
