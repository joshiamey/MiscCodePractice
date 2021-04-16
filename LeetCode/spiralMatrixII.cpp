/* LeetCode
* Sprial Matrix II
*Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.
*/

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

vector<vector<int>> spiralOrder(int n)
{
    vector<vector<int>> spiralmat(n, vector<int>(n));
    int frow = 0;
    int fcol = 0;
    int lrow = n - 1;
    int lcol = n - 1;
    int num = 1;

    while (frow <= lrow && fcol <= lcol && num <= (n * n))
    {
        // push back first row
        for (auto i = fcol; i <= lcol; ++i)
        {
            spiralmat[frow][i] = num++;
        }

        //push back first row + 1 until last row and last col
        for (auto j = frow + 1; j <= lrow; ++j)
        {
            spiralmat[j][lcol] = num++;
        }

        // if frow and lrow are same then this is already pushed back
        // no need to process
        if (frow < lrow)
        {
            for (auto k = lcol - 1; k > fcol; --k)
            {
                spiralmat[lrow][k] = num++;
            }
        }

        // if frow and lrow are same then this is already pushed back
        // no need to process
        if (fcol < lcol)
        {
            for (auto n = lrow; n > frow; --n)
            {
                spiralmat[n][fcol] = num++;
            }
        }

        //squeeze in to the center
        ++frow;
        ++fcol;
        --lrow;
        --lcol;
    }

    return spiralmat;
}

static void printMatrix(vector<vector<int>> mat)
{
    for (auto &row : mat)
    {
        for (auto &col : row)
        {
            cout << col << " ";
        }

        cout << endl;
    }
}

int main()
{
    cout << "Sprial matrix for 3: " << endl;
    printMatrix(spiralOrder(3));
    cout << "Sprial matrix for 4: " << endl;
    printMatrix(spiralOrder(4));
}