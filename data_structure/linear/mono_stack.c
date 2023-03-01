#include <stdio.h>

const int MAX = 3e6 + 10;
int n, src[MAX], ans[MAX];
int t, stk[MAX];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &src[i]);
    for (int i = n; i >= 1; i--)
    {
        while (t != -1 && src[stk[t]] <= src[i])
            t--;
        ans[i] = stk[t];
        stk[++t] = i;
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}