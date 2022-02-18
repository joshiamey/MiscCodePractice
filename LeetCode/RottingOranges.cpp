#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int orangesRotting(vector<vector<int>> &grid)
{
    int rr = grid.size();
    int cc = grid[0].size();

    int fresh = 0;
    vector<int> xdir = {0, 1, 0, -1};
    vector<int> ydir = {1, 0, -1, 0};
    queue<pair<int, int>> orangeQ;
    int time = 0;

    for (int i = 0; i < rr; ++i)
    {
        for (int j = 0; j < cc; ++j)
        {
            if (grid[i][j] == 2)
            {
                orangeQ.push({i, j});
            }
            else if (grid[i][j] == 1)
            {
                ++fresh;
            }
        }
    }

    // if they are no fresh oranges before the beginning of BFS/level order traversal
    // return 0
    if (fresh == 0)
        return 0;

    while (!orangeQ.empty())
    {
        if (fresh == 0)
            break;
        time++;
        auto queue_sz = orangeQ.size();
        for (auto i = 0; i < queue_sz; ++i)
        {
            auto pos = orangeQ.front();
            orangeQ.pop();
            int r = pos.first;
            int c = pos.second;

            for (int i = 0; i < 4; ++i)
            {
                auto x = r + xdir[i];
                auto y = c + ydir[i];

                if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || !grid[x][y] || grid[x][y] == 2)
                    continue;

                grid[x][y] = 2;
                orangeQ.push({x, y});
                fresh--;
            }
        }
    }

    return (!fresh) ? time : -1;
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> oranges = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 2}};

    // vector<vector<int>> oranges = {
    //     {1, 2}};

    cout << orangesRotting(oranges) << endl;
    return 0;
}
