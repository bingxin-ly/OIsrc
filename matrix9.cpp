#include <bits/stdc++.h>
using namespace std;
queue<string> qu;
map<string, bool> vis;
int n;

inline bool check(string ID)
{
    return ID == "123804765";
}
inline void save(string str)
{
    if (!vis[str])
        qu.push(str);
}
void update(string ID)
{
    n++;
    int pos = ID.find('0');
    string temp;
    // up
    if (pos / 3 > 1)
    {
        temp = ID;
        swap(temp[pos - 3], temp[pos]);
        save(temp);
    }
    // down
    if ((pos - 1) / 3 < 2)
    {
        temp = ID;
        swap(temp[pos + 3], temp[pos]);
        save(temp);
    }
    // left
    if (pos % 3 != 1)
    {
        temp = ID;
        swap(temp[pos - 1], temp[pos]);
        save(temp);
    }
    // right
    if (pos % 3)
    {
        temp = ID;
        swap(temp[pos + 1], temp[pos]);
        save(temp);
    }
}
void bfs()
{
    while (qu.size())
    {
        string ID = qu.front();
        qu.pop();
        if (check(ID))
            return;
        update(ID);
    }
}
int main()
{
    string zeroID = "283104765";
    // cin >> zeroID;
    // pos = zeroID.find('0');
    qu.push(zeroID);
    vis[zeroID] = true;
    bfs();
    cout << n;
}