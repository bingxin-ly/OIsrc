#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> res;

bool is_valid(vector<vector<int>> &board, int row, int col)
{
    int n = board.size();

    for (int i = 0; i <= row; i++)
        if (board[i][col] == 1)
            return false;

    for (int i = row - 1, j = col + 1;
         i >= 0 && j < n;
         i--, j++)
        if (board[i][j] == 1)
            return false;

    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0;
         i--, j--)
        if (board[i][j] == 1)
            return false;

    return true;
}

void bfs(vector<vector<int>> &board, int row)
{
    if (row == board.size())
    {
        res.push_back(board);
        return;
    }

    int n = board[row].size();
    for (int col = 0; col < n; col++)
    {
        if (!is_valid(board, row, col))
            continue;

        board[row][col] = 1;
        bfs(board, row + 1);
        board[row][col] = 0;
    }
}
void solve(int n)
{
    vector<vector<int>> board(n, vector<int>(n));
    bfs(board, 0);
}

int main()
{
    int n;
    cin >> n;
    solve(n);
    for (int i = 0; i < 3; i++)
    {
        for (auto j : res[i])
            for (int k = 0; k < j.size(); k++)
                if (j[k] == 1)
                    cout << k + 1 << ' ';
        cout << endl;
    }
    cout << res.size();
    return 0;
}