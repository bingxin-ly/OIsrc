#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5 + 5;
int n, m, R[N << 1];
char s[N], t[N << 1]{'!'};
signed main()
{
    while (scanf("%s", s + 1) != EOF)
    {
        n = strlen(s + 1), t[m = 1] = '@';
        for (int i = 1; i <= n; i++)
            t[++m] = s[i], t[++m] = '@';
        t[++m] = '#';

        int c = 0, r = 0;
        for (int i = 1; i < m; i++)
        {
            R[i] = i <= r ? min(R[2 * c - i], r - i + 1) : 1;
            while (t[i - R[i]] == t[i + R[i]])
                R[i] += 1;
            if (r < i + R[i] - 1)
            {
                r = i + R[i] - 1, c = i;
                if (i + R[i] - 1 == m - 1)
                {
                    printf("%s", s + 1);
                    for (int j = (i - R[i]) >> 1; j; j--)
                        putchar(s[j]);
                    // for (int p = 2; p < i; p += 2)
                    //     putchar(t[p]);
                    // for (int p = i - (i & 1); p; p -= 2)
                    //     putchar(t[p]);
                    putchar('\n');
                    break;
                }
            }
        }
    }
    return 0;
}