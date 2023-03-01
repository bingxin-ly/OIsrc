#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 10;
int n, c, pos[MAX];

bool check(int x)
{
    
}
int main()
{
    cin >> n >> c;
    for (int i = 1; i <= n; i++)
        cin >> pos[i];
    sort(pos + 1, pos + n + 1);

    int l, r;
    for (int i = 2; i <= n; i++)
        l = min(pos[i] - pos[i - 1], r);

    return 0;
}