/* Given a sorted array, create a new array containing squares 
of all the number of the input array in the sorted order.*/

#include <iostream>
#include <vector>
using namespace std;

class SquareSortedArray
{
private:
public:
    static vector<int> makesquares(const vector<int> &arr)
    {
        int n = arr.size();
        vector<int> squares(n);

        // initialize 2 pointers
        // i = start, which will point to smallest element in square rooted array
        // j = end. which shall point to largest element in the square rooted array
        auto i = 0;
        auto j = n - 1;

        // index k for inserting elements in square array
        auto k = n - 1;

        while (i < j)
        {
            auto a = arr[i] * arr[i];
            auto b = arr[j] * arr[j];

            // if the leftsquare (a) is <= right square(b) then store b at kth index, decrement j pointer
            // else store a at kth index, increment i pointer
            if (a <= b)
            {
                squares[k--] = b;
                --j;
            }
            else
            {
                squares[k--] = a;
                ++i;
            }
        }

        return squares;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> arr = {-2, -1, 0, 2, 3};

    auto res = SquareSortedArray::makesquares(vector<int>{-3, -2, 0, 3});

    for (auto r : res)
    {
        cout << r << " ";
    }
    cout << endl;

    res = SquareSortedArray::makesquares(arr);

    for (auto r : res)
    {
        cout << r << " ";
    }
    cout << endl;
    return 0;
}
