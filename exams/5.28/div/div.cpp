#include <bits/stdc++.h>
using namespace std;

struct mono_stack
{
    stack<int> src, stk;
    void push(int x)
    {
        src.push(x);
        while (!stk.empty() && stk.top() < x)
            stk.pop();
        stk.push(x);
    }
    void pop()
    {
        if (stk.empty())
            return;
        auto t = src.top();
        src.pop();
        if (stk.top() == t)
            stk.pop();
    }
    int getmx() { return stk.empty() ? 1 : stk.top(); }
    void clear()
    {
        while (!src.empty())
            src.pop();
        while (!stk.empty())
            stk.pop();
    }
} minn;
int cnt;

void sear(int n)
{
    queue<pair<int, int>> q;
    for (int i = 2, up = sqrt(n); i <= up; i++)
        if (n % i == 0 && i >= minn.getmx())
            q.emplace(i, n / i), cnt++;

    while (!q.empty())
    {
        auto t = q.front();
        q.pop();

        minn.push(t.first);
        sear(t.second);
        minn.pop();
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    while (n--)
    {
        cnt = 1, minn.clear();
        int x;
        cin >> x;
        sear(x);
        cout << cnt << '\n';
    }
    return 0;
}