#include <bits/stdc++.h>
using namespace std;

int a[100010], b[100010];
int main()
{
    int q;
    cin >> q;
    while (q--)
    {
        stack<int> stk;
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            cin >> b[i];

        for (int i = 1, cnt = 1; i <= n; i++)
        {
            stk.push(a[i]);
            while (stk.top() == b[cnt])
            {
                cnt++, stk.pop();
                if (stk.empty())
                    break;
            }
        }
        cout << (stk.empty() ? "Yes" : "No") << endl;
    }
    return 0;
}