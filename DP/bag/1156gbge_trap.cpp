#include <bits/stdc++.h>
#define chkmax(a, b) b > a ? a = b : a
using namespace std;

const int MAX = 110;
struct garbage
{
    int t, life, height;
    bool operator<(const garbage other) const
    {
        return t < other.t;
    }
} gs[MAX];
int d, g, f[MAX][MAX];

int main()
{
    cin >> d >> g;
    for (int i = 1, t, f, h; i <= g; i++)
        cin >> t >> f >> h, gs[i] = {t, f, h};
    sort(gs + 1, gs + g + 1);
    memset(f, ~0x7f, sizeof(f));

    f[0][0] = 10;
    int res = 0;
    for (int i = 1; i <= g; i++)
    {
        for (int j = d; j >= 0; j--)
        {
            if (f[i - 1][j] < gs[i].t - gs[i - 1].t)
                continue;
            if (j + gs[i].height >= d)
            {
                cout << gs[i].t;
                return 0;
            }
            chkmax(f[i][j + gs[i].height], f[i - 1][j] - (gs[i].t - gs[i - 1].t));
            chkmax(f[i][j], f[i - 1][j] + gs[i].life - (gs[i].t - gs[i - 1].t));
        }
        chkmax(res, f[i][0] + gs[i].t);
    }
    cout << res << endl;
    return 0;
}