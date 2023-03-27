#include <bits/stdc++.h>
using namespace std;

int n, val, sum, bcnt;
int main()
{
    ios::sync_with_stdio(false);
    char kind;
    cin >> n;
    priority_queue<int> q;
    for (int i = 1; i < n; i++)
    {
        cin >> kind >> val;
        if (kind == 'c')
        {
            q.push(-val);
            sum += val;
            bcnt++;
        }
        else
            while (bcnt >= val)
            {

                sum += q.top(), q.pop();
                bcnt--;
            }
    }
    cout << sum;
    return 0;
}