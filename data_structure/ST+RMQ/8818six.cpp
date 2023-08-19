#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5, LOG = 20, INF = INT_MAX;
int n, m, q, lg[N];
int amx[N][LOG], amn[N][LOG], anx[N][LOG], apn[N][LOG];
int bmx[N][LOG], bmn[N][LOG];
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        amx[i][0] = amn[i][0] = x;
        anx[i][0] = x < 0 ? x : ~INF;
        apn[i][0] = x >= 0 ? x : INF;
    }
    for (int i = 1; i <= m; i++)
        cin >> bmx[i][0], bmn[i][0] = bmx[i][0];

    for (int i = 2; i <= n || i <= m; i++)
        lg[i] = lg[i >> 1] + 1;
    for (int k = 1; k <= lg[n]; k++)
        for (int i = 1; i + (1 << k) - 1 <= n; i++)
        {
            int j = i + (1 << (k - 1));
            amx[i][k] = max(amx[i][k - 1], amx[j][k - 1]);
            anx[i][k] = max(anx[i][k - 1], anx[j][k - 1]);
            amn[i][k] = min(amn[i][k - 1], amn[j][k - 1]);
            apn[i][k] = min(apn[i][k - 1], apn[j][k - 1]);
        }
    for (int k = 1; k <= lg[m]; k++)
        for (int i = 1; i + (1 << k) - 1 <= m; i++)
        {
            int j = i + (1 << (k - 1));
            bmx[i][k] = max(bmx[i][k - 1], bmx[j][k - 1]);
            bmn[i][k] = min(bmn[i][k - 1], bmn[j][k - 1]);
        }

    for (int la, ra, lb, rb; q--;)
    {
        cin >> la >> ra >> lb >> rb;
        int sa = lg[ra - la + 1], sb = lg[rb - lb + 1];
        int pa = ra - (1 << sa) + 1, pb = rb - (1 << sb) + 1;

        int amax = max(amx[la][sa], amx[pa][sa]);
        int amin = min(amn[la][sa], amn[pa][sa]);
        int anmx = max(anx[la][sa], anx[pa][sa]);
        int apmn = min(apn[la][sa], apn[pa][sa]);
        int bmax = max(bmx[lb][sb], bmx[pb][sb]);
        int bmin = min(bmn[lb][sb], bmn[pb][sb]);

        long long ans = LLONG_MIN;
        ans = max(ans, 1ll * amax * (amax >= 0 ? bmin : bmax));
        ans = max(ans, 1ll * amin * (amin >= 0 ? bmin : bmax));
        if (anmx != ~INF)
            ans = max(ans, 1ll * anmx * (anmx >= 0 ? bmin : bmax));
        if (apmn != INF)
            ans = max(ans, 1ll * apmn * (apmn >= 0 ? bmin : bmax));
        cout << ans << '\n';
    }
    return 0;
}