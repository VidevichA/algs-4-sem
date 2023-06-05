#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>

int record1 = 0;
int record2 = 0;
std::vector<std::vector<int>> results1;
std::vector<std::vector<int>> results2;

bool isWhite(int i, int j)
{
    if (i % 2 == 0)
    {
        return j % 2 == 0;
    }
    else
    {
        return !(j % 2 == 0);
    }
}

void Solve(std::vector<std::vector<int>> &board, std::vector<int> &tempRes, int start, bool white)
{
    std::stack<int> data;
    for (int r = board.size() - 1; r >= 0; --r)
    {
        for (int c = board[0].size() - 1; c >= 0; --c)
        {
            if (white)
            {
                if (isWhite(r, c) && r * board[0].size() + c >= start && board[r][c] != -1)
                {
                    data.push(r * board[0].size() + c);
                }
            }
            else
            {
                if (!isWhite(r, c) && r * board[0].size() + c >= start && board[r][c] != -1)
                {
                    data.push(r * board[0].size() + c);
                }
            }
        }
    }
    while (!data.empty())
    {
        int el = data.top();
        data.pop();
        int y = std::ceil((double)(el + 1) / board[0].size()) - 1;
        int x = (el + 1) - (std::ceil((double)(el + 1) / board[0].size()) - 1) * board[0].size() - 1;
        std::vector<std::vector<int>> newBoard(board);
        int k = y;
        int p = x;
        while (k >= 0 && p >= 0 && newBoard[k][p] != -1)
        {
            newBoard[k--][p--] = 1;
        }
        k = y;
        p = x;
        while (k >= 0 && p < board[0].size() && newBoard[k][p] != -1)
        {
            newBoard[k--][p++] = 1;
        }
        k = y;
        p = x;
        while (k < board.size() && p >= 0 && newBoard[k][p] != -1)
        {
            newBoard[k++][p--] = 1;
        }
        k = y;
        p = x;
        while (k < board.size() && p < board[0].size() && newBoard[k][p] != -1)
        {
            newBoard[k++][p++] = 1;
        }
        bool flag = false;
        for (int i = 0; i < newBoard.size(); ++i)
        {
            for (int j = 0; j < newBoard[0].size(); ++j)
            {
                if (white)
                {
                    if (isWhite(i, j) && newBoard[i][j] == 0)
                    {
                        flag = true;
                        break;
                    }
                }
                else
                {
                    if (!isWhite(i, j) && newBoard[i][j] == 0)
                    {
                        flag = true;
                        break;
                    }
                }
            }
            if (flag)
            {
                break;
            }
        }
        tempRes.push_back(el);
        if (!flag)
        {
            if (white)
            {
                if (tempRes.size() == record1)
                {
                    record1 = tempRes.size();
                    results1.push_back(tempRes);
                }
                else if (tempRes.size() < record1)
                {
                    results1.clear();
                    record1 = tempRes.size();
                    results1.push_back(tempRes);
                }
            }
            else
            {
                if (tempRes.size() == record2)
                {
                    record2 = tempRes.size();
                    results2.push_back(tempRes);
                }
                else if (tempRes.size() < record2)
                {
                    results2.clear();
                    record2 = tempRes.size();
                    results2.push_back(tempRes);
                }
            }
            tempRes.pop_back();
        }
        else
        {
            if (white)
            {
                if (tempRes.size() + 1 <= record1)
                {
                    Solve(newBoard, tempRes, el + 1, true);
                }
            }
            else
            {
                if (tempRes.size() + 1 <= record2)
                {
                    Solve(newBoard, tempRes, el + 1, false);
                }
            }
            tempRes.pop_back();
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n, m, k;
    in >> n >> m >> k;
    std::vector<std::vector<int>> board = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));

    std::vector<int> tempRes1;
    std::vector<int> tempRes2;
    for (long long i = 0; i < k; ++i)
    {
        double temp;
        in >> temp;
        board[std::ceil(temp / m) - 1][temp - (std::ceil(temp / m) - 1) * m - 1] = -1;
    }
    std::vector<std::vector<int>> board2 = board;
    record1 = n * m - k;
    record2 = n * m - k;
    Solve(board, tempRes1, 0, true);
    Solve(board2, tempRes2, 1, false);
    long long counter = 0;
    std::vector<std::vector<int>> results;
    for (long long i = 0; i < results1.size(); ++i)
    {
        for (long long j = 0; j < results2.size(); ++j)
        {
            auto el = results1[i];
            for (long long r = 0; r < results2[j].size(); ++r)
            {
                el.push_back(results2[j][r]);
                std::sort(el.begin(), el.end());
            }
            results.push_back(el);
            ++counter;
        }
    }
    std::sort(results.begin(), results.end(), [](const std::vector<int> &f, const std::vector<int> &s)
              {
            for(long long i = 0; i < f.size(); ++i) {
                if(f[i] > s[i]) {
                    return false;
                }
                else if(f[i] < s[i])
                {
                    return true;
                }
            }
            return true; });
    for (auto r : results)
    {
        for (auto c : r)
        {
            out << c + 1 << ' ';
        }
        out << '\n';
    }
    out << counter;
    return 0;
}