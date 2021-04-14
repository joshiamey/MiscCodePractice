/* LeetCode
* Unique paths II , one with the obstacle
*/

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

static int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{

    auto m = obstacleGrid.size();
    auto n = obstacleGrid[0].size();

    vector<vector<int>> paths(m, vector<int>(n, 0));

    paths[0][0] = 1;

    for (auto i = 0; i < m; ++i)
    {
        for (auto j = 0; j < n; ++j)
        {
            if (obstacleGrid[i][j])
                continue;

            if (i - 1 >= 0)
                paths[i][j] += paths[i - 1][j];
            if (j - 1 >= 0)
                paths[i][j] += paths[i][j - 1];
        }
    }

    return paths[m - 1][n - 1];
}

int main()
{
    vector<vector<int>> vec{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    auto start = chrono::steady_clock::now();
    cout << "Word exists: " << uniquePathsWithObstacles(vec) << endl;
    auto end = chrono::steady_clock::now();
    cout << "Runtime in ms: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
}