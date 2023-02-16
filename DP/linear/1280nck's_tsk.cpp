#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e4 + 10;
int n, k, schedule[MAX], f[MAX];

struct task
{
    int p, t;
    bool operator<(const task &other) const
    {
        return (p > other.p); // 反向
    }
} tasks[MAX];

int main()
{
    cin >> n >> k;
    int p, t;
    for (int i = 1; i <= k; i++)
        cin >> tasks[i].p >> tasks[i].t, schedule[tasks[i].p]++;
    sort(tasks + 1, tasks + k + 1);
    int num = 1;
    for (int i = n; i >= 1; i--)
    {
        if (schedule[i] == 0)
            f[i] = f[i + 1] + 1;
        else
            for (int j = 1; j <= schedule[i]; j++)
            {
                f[i] = max(f[i], f[i + tasks[num].t]);
                num++;
            }
        cout << f[i] << endl;
    }
    cout << f[1] << endl;
    return 0;
}