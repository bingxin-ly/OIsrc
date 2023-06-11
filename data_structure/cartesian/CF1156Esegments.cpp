#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int top, st[N];
int n, src[N], rt, ls[N], rs[N];
void build()
{
    st[++top] = rt = 1;
    for (int i = 2; i <= n; i++)
    {
        int pre = 0;
        while (top && src[st[top]] < src[i])
            pre = st[top--];
        if (pre)
            ls[i] = pre;
        if (!top)
            rt = i;
        else
            rs[st[top]] = i;
        st[++top] = i;
    }
}

int ans;
set<int> s[N];
void merge(int x, int y)
{
    if (s[y].size() > s[x].size())
        swap(s[x], s[y]);
    for (int i : s[y])
        if (s[x].count(src[x] - i))
            ans++;
    for (int i : s[y])
        s[x].insert(i);
}
void dfs(int x)
{
    if (ls[x])
        dfs(ls[x]), merge(x, ls[x]);
    if (rs[x])
        dfs(rs[x]), merge(x, rs[x]);
    s[x].insert(src[x]);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> src[i];
    build();

    dfs(rt);
    cout << ans;
    return 0;
}