#include <bits/stdc++.h>
using namespace std;

int a[40][40];
int main()
{
    int n;
    cin >> n;
    int x = 1, y = (n + 1) / 2;
    for (int i = 1, up = n * n; i <= up; i++)
    {
        a[x][y] = i;
        if (!a[(x - 2 + n) % n + 1][y % n + 1])
            x = (x - 2 + n) % n + 1, y = y % n + 1;
        else
            x = x % n + 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << ' ';
        cout << '\n';
    }
}
