int **son, *cnt, idx;

void init(int maxn, int char_num = 80)
{
    son = new int*[maxn];
    for (int i = 0; i < maxn; i++)
        son[i] = new int[char_num]();
    cnt = new int[maxn];
}
void insert(const char *str)
{
    int p = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int u = str[i] - '0'; // 小心0
        if (!son[p][u])
            son[p][u] = ++idx;
        p = son[p][u];
        cnt[p]++; // 位置灵活
    }
}
int query(const char *str)
{
    int p = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        int u = str[i] - '0';
        if (!son[p][u])
            return 0;
        p = son[p][u];
    }
    return cnt[p];
}
