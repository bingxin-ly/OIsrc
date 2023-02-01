#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 * 50 + 10;
int son[MAXN][30], cnt[MAXN], idx;

void insert(const char *str)
{
    int p = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int u = str[i] - 'a'; // 小心0
        if (!son[p][u])
            son[p][u] = ++idx;
        p = son[p][u];
    }
    cnt[p]++; // 位置灵活
}
int query(const char *str)
{
    int p = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int u = str[i] - 'a';
        if (!son[p][u])
            return 0;
        p = son[p][u];
    }
    return cnt[p]++;
}

int main()
{
    int n, m;
    char tmp[60];
    cin >> n;
    while (n--)
        cin >> tmp, insert(tmp);
    cin >> m;
    while (m--)
    {
        cin >> tmp;
        auto res = query(tmp);
        switch (res)
        {
            case 1:
                cout << "OK" << endl;
                break;
            case 0:
                cout << "WRONG" << endl;
                break;
            default:

                cout << "REPEAT" << endl;
                break;

        }
    }
    return 0;
}