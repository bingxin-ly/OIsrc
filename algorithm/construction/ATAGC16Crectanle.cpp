#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int H, W, h, w;
    cin >> H >> W >> h >> w;
    if (H % h == 0 && W % w == 0)
        return cout << "No", 0;
    cout << "Yes" << '\n';
    int val = (h * w - 1) * 500 + 1;
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
            if (i % h == 0 && j % w == 0)
                cout << -val << ' ';
            else
                cout << "500 ";
        cout << '\n';
    }
    return 0;
}