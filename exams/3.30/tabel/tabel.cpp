#include <bits/stdc++.h>
using namespace std;

string str;
vector<char> letters;
map<char, int> idx;

bool vis[20], mp[20];
bool calc(bool a, bool b, char op)
{
    switch (op)
    {
    case '&':
        return a && b;
    case '|':
        return a || b;
    case '>':
        if ((a == b) || (!a && b))
            return true;
        else
            return false;
    case '=':
        return (a == b);
    }
}

int n, pos[20];
stack<int> pars;
queue<bool> ress;
queue<char> ops;
void dfs(int now)
{
    if (now == n + 1)
    {
        cout << endl;
        for (int i = 1; i <= n; i++)
            cout << mp[i] << ' ';
        cout << endl;

        int a, b, no, cnt;
        a = b = no = cnt = 0;
        for (auto i : str)
        {
            cnt++;
            if (i == '(')
                pars.push(cnt);
            else if (65 <= i && i <= 90)
            {
                ress.push((no % 2) != 0 == (!mp[idx[i]]));
                cout << "push " << ress.back() << " when no = " << no << endl;
                no = 0;
            }
            else if (i == ')')
            {
                a = ress.front();
                ress.pop();
                while ( > 0)
                {
                    b = ress.front();
                    ress.pop();

                    cout << "Now to calc! " << ress.size() << ", " <<  << ": " << a << ' ' << ops.front() << ' ' << b << endl;
                    a = calc(a, b, ops.front());
                    ops.pop();
                }
                ress.push(a);
            }
            else if (i == '!')
                no++;
            else
                ops.push(i);
        }
        /* while (ress.size() >= 2)
        {
            a = ress.top();
            ress.pop();
            b = ress.top();
            ress.pop();

            ress.push(calc(b, a, ops.top())); // TODO
        } */
        cout << ress.back();
        ress.pop();
        return;
    }

    for (int i = 0; i <= 1; i++)
    {
        if (vis[now])
            continue;
        vis[now] = true;
        mp[now] = i;
        dfs(now + 1);
        vis[now] = false;
    }
}

int tot;
int main()
{
    ios::sync_with_stdio(false);

    while (cin >> str && !str.empty())
    {
        tot = n = 0;
        letters.clear(), idx.clear();
        memset(vis, false, sizeof(vis));
        while (!ops.empty())
            ops.pop();
        while (!ress.empty())
            ress.pop();

        for (auto i : str)
            if (65 <= i && i <= 90)
                letters.push_back(i);

        sort(letters.begin(), letters.end());
        letters.erase(unique(letters.begin(), letters.end()), letters.end());

        for (auto i : letters)
            idx[i] = ++tot;

        n = letters.size();
        dfs(1);
        cout << '\n';
    }
    return 0;
}
