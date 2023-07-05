bitset<100000001> vis;
void sieve(int n)
{
    vis.set();
    vis[0] = vis[1] = 0;
    for (int i = 2, up = sqrt(n); i <= up; i++)
        if (vis[i])
            for (int j = i * i; j <= n; j += i)
                vis[j] = 0;
}