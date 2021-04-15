/* LeetCode
* Sprial Matrix I
*/

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    vector<int> spiral;
    int frow = 0;
    int fcol = 0;
    int lrow = matrix.size() - 1;
    int lcol = matrix[0].size() - 1;

    while (frow <= lrow && fcol <= lcol)
    {
        // push back first row
        for (auto i = fcol; i <= lcol; ++i)
        {
            spiral.push_back(matrix[frow][i]);
        }

        //push back first row + 1 until last row and last col
        for (auto j = frow + 1; j <= lrow; ++j)
        {
            spiral.push_back(matrix[j][lcol]);
        }

        // if frow and lrow are same then this is already pushed back
        // no need to process
        if (frow < lrow)
        {
            for (auto k = lcol - 1; k > fcol; --k)
            {
                spiral.push_back(matrix[lrow][k]);
            }
        }

        // if frow and lrow are same then this is already pushed back
        // no need to process
        if (fcol < lcol)
        {
            for (auto n = lrow; n > frow; --n)
            {
                spiral.push_back(matrix[n][fcol]);
            }
        }

        //squeeze in to the center
        ++frow;
        ++fcol;
        --lrow;
        --lcol;
    }

    return spiral;
}

void execute(vector<vector<int>> &vec)
{
    auto start = chrono::steady_clock::now();
    auto spiral = spiralOrder(vec);
    auto end = chrono::steady_clock::now();
    cout << "Runtime in ms: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    cout << "Spiral order for given matrix" << endl;
    for (auto &elem : spiral)
        cout << elem << " ";
    cout << endl;
}

int main()
{
    vector<vector<int>> vec{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> vec2{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    vector<vector<int>> vec3{{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    vector<vector<int>> vec4{{1, 2, 3}, {4, 5, 6}};
    vector<vector<int>> vec5{{1}, {4}, {5}};
    vector<vector<int>> vec6{{1, 2, 3}};

    execute(vec);
    execute(vec2);
    execute(vec3);
    execute(vec4);
    execute(vec5);
    execute(vec6);
}