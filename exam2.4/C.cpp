#include <bits/stdc++.h>
using namespace std;

const int MAX = 5e4 + 10;
int n, m, room[MAX];

void setmem(int st, int ed, int val)
{
    for (int i = st; i <= ed; i++)
        room[i] = val;
}
int query(int len)
{
    for (int i = 1; i <= n; i++)
    {
        if (room[i] == 1)
            continue;
        bool flag = true;
        for (int j = i; j <= min(i + len - 1, n) && flag; j++)
        {
            if (room[j] == 1)
            {
                flag = false;
                break;
            }
        }
        if(i + len - 1 > n) return 0;
        setmem(i, i + len - 1, 1);
        return i;
    }
    return 0;
}
void quit(int l, int len)
{
    setmem(l, l + len - 1, 0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int op, a, b;
    while (m--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> a;
            cout << query(a) << endl;
        }
        else
            cin >> a >> b,
                quit(a, b);
    }
    return 0;
}