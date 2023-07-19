// AdvancedGuide\DP\0x5EPractice\315Trip.md
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 90;
int n, m;
int prea[N][26], preb[N][26], // 记录串 A 前 i 个字符中最近的字符 c 的位置
    f[N][N];
char a[N], b[N], ans[N];

vector<char> last[N][N];
void print(int i, int j, int len)
{
    if (f[i][j] == 1)
        return ans[len] = '\0', cout << ans << '\n', void();
    for (char ch : last[i][j]) // 每个位置有这么多种可能
        ans[len] = ch,
        print(prea[i - 1][ch - 'a'], preb[j - 1][ch - 'a'], len + 1);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> (a + 1) >> (b + 1), n = strlen(a + 1), m = strlen(b + 1);
    reverse(a + 1, a + n + 1), reverse(b + 1, b + m + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int ch = 0; ch < 26; ch++)
            prea[i][ch] = prea[i - 1][ch];
        prea[i][a[i] - 'a'] = i;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int ch = 0; ch < 26; ch++)
            preb[i][ch] = preb[i - 1][ch];
        preb[i][b[i] - 'a'] = i;
    }
    a[++n] = b[++m] = '#'; // 添加一个结束标志位
    memset(f, ~0x3f, sizeof(f)), f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i] == b[j])
                for (char ch = 'a'; ch <= 'z'; ch++) // 看看上一个从哪里导来的
                {
                    int pa = prea[i - 1][ch - 'a'], pb = preb[j - 1][ch - 'a'];
                    if (f[pa][pb] + 1 > f[i][j])
                    {
                        f[i][j] = f[pa][pb] + 1;
                        last[i][j].clear(), last[i][j].emplace_back(ch);
                    }
                    else if (f[pa][pb] + 1 == f[i][j])
                        last[i][j].emplace_back(ch);
                }
    print(n, m, 0);
    return 0;
}