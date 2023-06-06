#include <bits/stdc++.h>
using namespace std;

const int MAX = 3e6 + 10;
int n, src[MAX], ans[MAX];
stack<int> stk;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> src[i];
    for (int i = n; i >= 1; i--)
    {
        while (!stk.empty() && src[stk.top()] <= src[i])
            stk.pop();
        ans[i] = stk.empty() ? 0 : stk.top();
        stk.push(i);
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    return 0;
}