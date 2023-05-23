#include <bits/stdc++.h>
using namespace std;

const int N = 3e6;
/* struct node
{
    char data;
    bool is_end;
    unordered_map<int, node *> ch;
}; deprecated */
int son[N][80], cnt[N], idx;
// 0号点既是根节点，又是空节点
// son[][]存储树中每个节点的子节点
// cnt[]存储以每个节点结尾的单词数量

// 插入一个字符串
void insert(const char *str)
{
    int p = 0;
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - '0'; // 起始位置
        if (!son[p][u])
            son[p][u] = ++idx;
        p = son[p][u];
        cnt[p]++; // 题目中要求的是为前缀即可，所以放这里
    }
}

// 查询字符串出现的次数
int query(const char *str)
{
    int p = 0;
    for (int i = 0; str[i]; i++)
    {
        int u = str[i] - '0';
        if (!son[p][u])
            return 0;
        p = son[p][u];
    }
    return cnt[p];
}

char tmp[N];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 0; i <= idx; i++)
        {
            for (int j = 0; j < 80; j++)
                son[i][j] = 0;
            cnt[i] = 0;
        }
        idx = 0;
        int n, q;
        scanf("%d%d", &n, &q);
        for (int i = 0; i < n; i++)
            scanf("%s", tmp), insert(tmp);
        for (int i = 0; i < q; i++)
            scanf("%s", tmp), printf("%d\n", query(tmp));
    }
    return 0;
}