#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    bool exist(vector<vector<char>> &board, string word)
    {
        for (auto i = 0; i < board.size(); ++i)
        {
            for (auto j = 0; j < board[0].size(); ++j)
            {
                if (board[i][j] == word[0])
                {
                    if (doDfs(board, word, i, j, 0))
                        return true;
                }
            }
        }

        return false;
    }

    bool doDfs(vector<vector<char>> &board, string word, int row, int col, int l)
    {
        bool retval = false;
        if (l == word.length())
            return true;

        if (row < 0 || col < 0 || row >= board.size() || col >= board[0].size())
            return false;

        if (board[row][col] == word[l])
        {
            char temp = board[row][col];
            //mark item as visited;
            board[row][col] = '#';
            retval = doDfs(board, word, row + 1, col, l + 1) | // veritcal up
                     doDfs(board, word, row - 1, col, l + 1) | // vertical down
                     doDfs(board, word, row, col + 1, l + 1) | // horizontal right
                     doDfs(board, word, row, col - 1, l + 1);  // horizontal left

            /* restore the value */
            board[row][col] = temp;
        }

        return retval;
    }
};

int main()
{
    Solution s;
    vector<vector<char>> vec{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};

    cout << "Word exists: " << s.exist(vec, "ABCCED") << endl;
}