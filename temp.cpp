#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, greater<>> heap;
signed main()
{
    int n;
    cin >> n;
    for (int i = 1, x; i <= n; i++)
        cin >> x, heap.emplace(x);
    int a, b, ans = 0;
    while (heap.size() > 1)
    {
        a = heap.top(), heap.pop(), b = heap.top(), heap.pop();
        heap.emplace(a + b);
        ans += heap.top();
    }
    cout << ans;
    return 0;
}