#include <iostream>
using namespace std;

const int N = 10010, M = 100010;

int n, m;
char p[N], s[M];
int nxt[N];

int main()
{
    cin >> n >> p + 1 >> m >> s + 1;

    // 求nxt数组
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && p[i] != p[j + 1])
            j = nxt[j];
        if (p[i] == p[j + 1])
            j++;
        nxt[i] = j;
    }

    // kmp匹配过程
    for (int i = 1, j = 0; i <= m; i++)
    {
        while (j && s[i] != p[j + 1])
            j = nxt[j];
        if (s[i] == p[j + 1])
            j++;
        if (j == n)
        {
            printf("%d", i - n);
            j = nxt[j];
        }
    }
    return 0;
}