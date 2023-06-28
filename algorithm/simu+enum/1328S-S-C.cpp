#include <bits/stdc++.h>
using namespace std;

int res[][5]{{0, -1, 1, 1, -1},
             {1, 0, -1, 1, -1},
             {-1, 1, 0, -1, 1},
             {-1, -1, 1, 0, 1},
             {1, 1, -1, -1, 0}};
int a[200], b[200];
signed main()
{
    int n, al, bl;
    cin >> n >> al >> bl;
    for (int i = 0; i < al; i++)
        cin >> a[i];
    for (int i = 0; i < bl; i++)
        cin >> b[i];

    int aa = 0, ba = 0;
    for (int i = 0; i < n; i++)
    {
        int t = res[a[i % al]][b[i % bl]];
        if (t == 1)
            aa += 1;
        else if (t == -1)
            ba += 1;
    }
    cout << aa << ' ' << ba;
    return 0;
}