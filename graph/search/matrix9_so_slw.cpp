#include <bits/stdc++.h>
using namespace std;

struct state
{
    string status;
    int dep;
};
queue<state> qu;
map<string, bool> vis;
int n;

inline bool check(string ID)
{
    return ID == "123804765";
}
inline void save(string proced, int dep)
{
    if (!vis[proced])
        qu.push((state){proced, dep + 1});
}
void bfs()
{
    while (!qu.empty())
    {
        state now = qu.front();
        qu.pop();
        if (check(now.status))
        {
            cout << now.dep << endl;
            return;
        }
        int i = now.status.find('0');
        string temp;
        // up
        if (i >= 3 && i <= 8)
        {
            temp = now.status;
            swap(temp[i - 3], temp[i]);
            save(temp, now.dep);
        }
        // down
        if (i >= 0 && i <= 5)
        {
            temp = now.status;
            swap(temp[i + 3], temp[i]);
            save(temp, now.dep);
        }
        // left
        if (i % 3 == 1 || i % 3 == 2)
        {
            temp = now.status;
            swap(temp[i - 1], temp[i]);
            save(temp, now.dep);
        }
        // right
        if (i % 3 == 1 || i % 3 == 0)
        {
            temp = now.status;
            swap(temp[i + 1], temp[i]);
            save(temp, now.dep);
        }
    }
}

int main()
{
    string id;
    cin >> id;
    qu.push((state){id, 0});
    vis[id] = true;
    bfs();
}