#include <cstdio>
using namespace std;

int stk[1000];
int main()
{
    int i = 0, now = 0;
    char op;
    while ((op = getchar()) != '@')
    {
        if (op >= '0' && op <= '9')
            now *= 10, now += op - '0';
        else if (op == '.')
        {
            stk[++i] = now;
            now = 0;
        }
        else if (op == '+')
        {
            stk[i - 1] = stk[i - 1] + stk[i];
            stk[i--] = 0;
        }
        else if (op == '-')
        {
            stk[i - 1] = stk[i - 1] - stk[i];
            stk[i--] = 0;
        }
        else if (op == '*')
        {
            stk[i - 1] = stk[i - 1] * stk[i];
            stk[i--] = 0;
        }
        else if (op == '/')
        {
            stk[i - 1] = stk[i - 1] / stk[i];
            stk[i--] = 0;
        }
    }
    printf("%d", stk[1]);
    return 0;
}