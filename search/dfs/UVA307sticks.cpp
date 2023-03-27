#include <bits/stdc++.h>
using namespace std;

int n, len, cnt, ss[70], vis[70];

/**
 * @param num 当前拼好的根数
 * @param cat 当前拼好的长度
 * @param prev 上一根木棍的长度
 */
bool dfs(int num, int cat, int prev)
{
    if (num > cnt)
        return true;
    if (cat == len)
        return dfs(num + 1, 0, 0); // 这根已经拼好

    int tried = 0; // 2. 记录的是最近一次尝试拼接的木棍长度
    /* 3. 限制先后加入一根原始木棍的长度是递减的。
    因为先拼上一个长为x的木棍再拼上一个长为y的木棍，
    等效于先拼上一个长为y的木棍再拼上一个长为x的木棍。
    所以只需要搜索其中一种即可。*/
    for (int i = prev; i <= n; i++)
        if (!vis[i] &&
            ss[i] + cat <= len &&
            tried != ss[i])
        {
            vis[i] = true;
            if (dfs(num, cat + ss[i], i))
                return true;
            vis[i] = false;
            tried = ss[i];
            if (!cat || cat + ss[i] == len)
                return false;
            /* 4. 5. 
            如果在一根原始木棒中尝试拼接的第一根木棍的递归分支就以失败返回，直接判断当前分支无解。
            与此同时，如果两个木棍的长度和与一个木棍的一样，
            只尝试一个的就行了(因为前两个可能会有更大的效用) */
        }
    return false;
}
int main()
{
    while (cin >> n, n)
    {
        int sum = 0;
        for (int i = 1; i <= n; i++)
            cin >> ss[i], sum += ss[i];

        sort(ss + 1, ss + n + 1), reverse(ss + 1, ss + n + 1);
        // 1. 优先尝试较长的木棍
        for (len = ss[1]; len <= sum; len++)
        {
            if (sum % len)
                continue;
            cnt = sum / len;
            memset(vis, false, sizeof(vis));
            if (dfs(1, 0, 0))
            {
                cout << len << endl;
                break;
            }
        }
    }
    return 0;
}