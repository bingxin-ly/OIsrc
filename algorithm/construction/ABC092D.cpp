#include <bits/stdc++.h>
using namespace std;

char BLACK = '#', WHITE = '.', w[100][100];
void paint(char col, int lim, int fr, int to)
{
    if (lim == 0)
        return;
    int cnt = 0;
    for (int i = fr; i <= to; i += 2)
        for (int j = 2; j <= 90; j += 2)
        {
            w[i][j] = col;
            if (++cnt == lim)
                return;
        }
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int a, b;
    cin >> a >> b;
    for (int i = 1; i <= 50; i++)
        for (int j = 1; j <= 90; j++)
            w[i][j] = BLACK;
    for (int i = 51; i <= 90; i++)
        for (int j = 1; j <= 90; j++)
            w[i][j] = WHITE;
    paint(WHITE, a - 1, 2, 50), paint(BLACK, b - 1, 52, 90);
    cout << "90 90\n";
    for (int i = 1; i <= 90; i++)
    {
        for (int j = 1; j <= 90; j++)
            cout << w[i][j];
        cout << '\n';
    }
    return 0;
}