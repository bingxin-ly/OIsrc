#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 10;
int n, k, arr[MAX], mins[MAX], maxs[MAX];
int qmin[MAX], qmax[MAX]; // 数组模拟队列

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    memset(mins, 0x7f, sizeof(mins));

    int l = 1, r = 1;
    for (int i = 1; i <= n; i++)
    {
        while (l <= r && qmin[l] < i - k)
            l++;
        mins[i] = arr[qmin[l]];
        while (l <= r && arr[qmin[r]] >= arr[i])
            r--;
        qmin[++r] = i;
    }
    l = 1, r = 1;
    for (int i = 1; i <= n; i++)
    {
        while (l <= r && qmax[l] < i - k)
            l++;
        maxs[i] = arr[qmax[l]];
        while (l <= r && arr[qmax[r]] <= arr[i])
            r--;
        qmax[++r] = i;
    }

    for (int i = k; i <= n; i++)
        cout << mins[i] << " ";
    puts("");
    for (int i = k; i <= n; i++)
        cout << maxs[i] << " ";
    return 0;
}