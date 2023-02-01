#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3 * 1e6;
int son[MAXN][80], cnt[MAXN], idx;

void insert(string str)
{
    int p = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int u = str[i] - '0'; // 小心0
        if (!son[p][u])
            son[p][u] = ++idx;
        p = son[p][u];
        cnt[p]++;
    }
}
int query(string str)
{
    int p = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int u = str[i] - '0';
        if (!son[p][u])
            return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        for (int i = 0; i <= idx; i++)
            for (int j = 0; j <= 79; j++) //注意清除时是减掉下标的值
                son[i][j] = 0;
        for (int i = 0; i <= idx; i++)
            cnt[i] = 0;
        idx = 0;
        int n, q;
        cin >> n >> q;
        string tmp;
        for (int i = 0; i < n; i++)
            cin >> tmp, insert(tmp);
        for (int i = 0; i < q; i++)
            cin >> tmp, cout << query(tmp) << endl;
    }
    return 0;
}