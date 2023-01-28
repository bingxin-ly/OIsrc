#include <bits/stdc++.h>
using namespace std;

int n, m;
int pics[1000010], vis[2010];
int l, r, a, b;
int flag;

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", pics + i);
    l = r = 1;
    vis[pics[1]] = 1;
    flag = 1;
    while (l <= r && r <= n)
    {
        if (flag == m)
        {
            if (a == 0 && b == 0)
                a = l, b = r;
            else if (r - l < b - a)
                a = l, b = r;
            vis[pics[l]]--;
            if (vis[pics[l]] == 0)
                flag--;
            l++;
        }
        else
        {
            r++, vis[pics[r]]++;
            if (vis[pics[r]] == 1)
                flag++;
        }
    }
    printf("%d %d", a, b);
}