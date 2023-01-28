#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int end, w;
};
struct node
{
    int id, rank, c, u;
    vector<edge> connect;
};

int n, p, highest_rank;
vector<node> neu;

int main()
{
    cin >> n >> p;
    neu.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        neu[i].id = i, neu[i].rank = 1;
        cin >> neu[i].c >> neu[i].u;
    }
    int st, ed, w;
    for (int i = 1; i <= p; i++)
    {
        cin >> st >> ed >> w;
        neu[st].connect.push_back({ed, w});
        neu[ed].rank = neu[st].rank + 1;
        highest_rank = max(highest_rank, neu[ed].rank);
    }
    for (int i = 1; i <= n; i++)
    {
        if (neu[i].rank == 1 && neu[i].c > 0)
        {
            for (auto j : neu[i].connect)
                neu[j.end].c += neu[i].c * j.w;
        }
    }
    for (int r = 2; r <= highest_rank; r++)
    {
        for (int i = 1; i <= n; i++)
        {
            if ((neu[i].c - neu[i].u) > 0 && neu[i].rank == r)
            {
                for (auto j : neu[i].connect)
                    neu[j.end].c += (neu[i].c - neu[i].u) * j.w;
            }
        }
    }
    bool flag = true;
    for (auto &i : neu)
    {
        if (i.c > 0 && i.connect.empty())
            flag = false, cout << i.id << " " << (i.rank == 1 ? i.c : i.c - i.u) << endl;
    }
    if (flag)
        cout << "NULL";
    return 0;
}