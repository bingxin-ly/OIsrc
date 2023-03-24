#include <bits/stdc++.h>
using namespace std;

int m = 9, n = 9, board[10][10], nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

bool is_valid(int i, int j, int n)
{
    for (int x = 0; x < 9; x++)
    {
        if (board[i][x] == n)
            return false;
        if (board[x][j] == n)
            return false;
        if (board[(i / 3) * 3 + x / 3][(j / 3) * 3 + x % 3] == n)
            return false;
    }
    return true;
}
int solve(int i, int j)
{
    if (i == m)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
                cout << board[i][j] << ' ';
            cout << endl;
        }
        exit(0);
    }
    if (j == n)
        return solve(i + 1, 0), 0;
    if (board[i][j])
        return solve(i, j + 1), 0;

    for (int n = 1; n <= 9; n++)
    {
        if (!is_valid(i, j, n))
            continue;
        board[i][j] = n;
        solve(i, j + 1);
        board[i][j] = 0;
    }
    return 0;
}
int main()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            cin >> board[i][j];

    solve(0, 0);
    return 0;
}
