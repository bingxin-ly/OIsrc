#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int cnt;
unordered_map<int, pair<int, int>> raw, col;

int main()
{
    int T, n, m, q;
    cin >> T;
    while (T--)
    {
        cnt = 0;
        raw.clear(), col.clear();
        cin >> n >> m >> q;
        while (q--)
        {
            int op, x, c;
            cin >> op >> x >> c;
            if (op) // raw
                col[x] = {++cnt, c};
            else
                raw[x] = {++cnt, c};
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
                cout << max(raw[i], col[j]).second << ' ';
            cout << endl;
        }
    }
    return 0;
}