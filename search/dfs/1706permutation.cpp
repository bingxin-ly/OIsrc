#include <bits/stdc++.h>
using namespace std;

int n, arr[10];
bool vis[10];
void dfs(int now)
{
    if (now == n)
    {
        for (int i = 0; i < n; i++)
            cout << setw(5) << arr[i];
        puts("");
        return;
    }
    for (int i = 0; i < n; i++)
        if (!vis[i])
        {
            vis[i] = true;
            arr[now] = i;
            dfs(now + 1);
            vis[i] = false;
        }
}

int main()
{
    cin >> n;
    dfs(0);
/*     iota(arr, arr + n, 1);
    reverse(arr, arr + n);
    int fact = 1;
    for (int i = 1; i <= n; i++)
        fact *= i;
    while (fact--)
    {
        next_permutation(arr, arr + n);
        for (int i = 0; i < n; i++)
            cout << setw(5) << arr[i];
        puts("");
    } */
    return 0;
}