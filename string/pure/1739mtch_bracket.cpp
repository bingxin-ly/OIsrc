#include <bits/stdc++.h>
using namespace std;

int main()
{
    int ok = 0;
    char c;
    while (true)
    {
        c = getchar();
        if (c == '(')
            ok++;
        if (c == ')')
            ok--;
        if (ok < 0)
        {
            printf("NO");
            return 0;
        }
        if (c == '@')
        {
            if (!ok)
                printf("YES");
            else
                printf("NO");
            return 0;
        }
    }
}
