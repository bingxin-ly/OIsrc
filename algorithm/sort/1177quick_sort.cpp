#include <bits/stdc++.h>
using namespace std;

int n, arr[100010];
void qsort(int l, int r)
{
    if (l >= r)
        return;
    int i = l, j = r, base = arr[rand() % (r - l + 1) + l];
    while (i < j)
    {
        while (arr[i] < base)
            i++;
        while (arr[j] > base)
            j--;
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (l < j)
        qsort(l, j);
    if (i < r)
        qsort(i, r);
}
int main()
{
    srand(time(0));
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    qsort(0, n - 1);
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    return 0;
}