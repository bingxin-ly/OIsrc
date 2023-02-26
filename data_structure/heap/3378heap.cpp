#include <bits/stdc++.h>
using namespace std;

int n;
priority_queue<int> heap;
int main()
{
    cin >> n;
    for (int i = 1, op, k; i <= n; i++)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> k;
            heap.push(-k);
            break;
        case 2:
            cout << -heap.top() << endl;
            break;
        case 3:
            heap.pop();
        }
    }
    return 0;
}