#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e3 + 10;
int n, m, ans, s;
int st[MAX], tuopu[MAX][MAX], in[MAX], tt[MAX], top;
bool stop[MAX], vis[MAX];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        memset(stop, 0, sizeof(stop));
        cin >> s;
        for (int j = 1; j <= s; j++)
            cin >> st[j], stop[st[j]] = true;
        for (int j = st[1]; j <= st[s]; j++)
            if (!stop[j])
                for (int k = 1; k <= s; k++)
                    if (!tuopu[j][st[k]])
                        tuopu[j][st[k]] = 1, in[st[k]]++;
    }

    do
    {
        top = 0;
        for (int i = 1; i <= n; i++)
            if (!in[i] && !vis[i])
                tt[++top] = i, vis[i] = true;

        for (int i = 1; i <= top; i++)
            for (int j = 1; j <= n; j++)
                if (tuopu[tt[i]][j])
                    tuopu[tt[i]][j] = 0, in[j]--; // 删点，层数减一
        ans++;
    } while (top);
    cout << ans - 1;
    
    return 0;
}
